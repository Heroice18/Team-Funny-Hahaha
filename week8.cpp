#include <iostream>
#include <iomanip>
using namespace std;

/****************************************
 * ARRAY VULNERABILTY
 * 1. There must be an array and an array index variable
 * 2. The array index variable must be reachable through external input.
 * 3. There must not be bounds checking on the array index variable.
 ****************************************/
void arrayVulnerability(int num)
{
   //The array has a size of 10
   int array[10] = {1, 1, 2, 3, 5, 8, 13, 21, 34, 55};
   // Pretend to ask the user to give a sense of realism
   cout << "Which of the first 10 Fibbonacchi number would you like to see?\n";
   cout << "num passed is: " << num << endl;
   // Subtract one from the number because arrays start at 0
   cout << "array[" << num - 1 << "] = " << array[num - 1] << endl;
}

/**************************************
 * ARRAY WORKING
 * Call arrayVulnerability() in a way that does
 * not yield unexpected behavior
 *************************************/
void arrayWorking()
{
   //index 4 is within the bounds of the array, normal behavior expected
   arrayVulnerability(5);
}

/* ***************************************
 * Array Exploit
 * In order for an array index exploit to happen, the following
 * must occur:
 * 1) There must be an array and an array index variable
 * 2) The array index variable must be reachable through
 *    external input
 * 3) There must not be bounds checking on the array index
 *    variable
 * ***************************************/
void arrayExploit()
{
   //index 10 is outside the bounds of the array
   // but the lack of check makes this an exploit
   arrayVulnerability(11);
}

void safe()
{
   cout << "SAFE\n";
}

void dangerous()
{
   cout << "Dangerous\n";
}

/**************************************
 * ARC VULNERABILITY
 * 1. There must be a function pointer used in the code
 * 2. Through some vulnerability there must be some way for user input to overwrite the function pointer.
 *    This typically happens through a stack buffer vulnerability.
 * 3. After the memory is overwriten the function pointer must be dereferenced
 *************************************/
void arcVulnerability(long input[], int numElements)
{
   long buffer[4];
   void (* pointerFunction)() = safe;
   for (int i = 0; i < numElements; ++i) 
   {
      buffer[i] = input[i];
   }
   pointerFunction();
}

 /**************************************
 * ARC VULNERABILITY
 * Call arrayVulnerability() in a way that does
 * not yield unexpected behavior
 *************************************/ 
void arcWorking()
{
   cout << "-------ARC WORKING------\n";
   long buffer[4] = {1,2,3,4};
   arcVulnerability(buffer, 4);
}

/**************************************
 * ARC EXPLOIT
 * 1. The attacker provides an array with 5 elements the 5th being
 *    the address of dangerous.
 * 2. The buffer in arcVulnerability() only holds 4 elements so the 5th
 *    overflows into the pointer function rewriting the address
 * 3. When the pointer function is called later the pointer function is called
 *************************************/
void arcExploit()
{
   cout << "-------ARC EXPLOIT------\n";
   long largeBuffer[5] = {1,2,3,4, (long) &dangerous};
   arcVulnerability(largeBuffer, 5);
}

/***************************************
 * VTABLE SPRAYING/SMASHING
 * 1. The vulnerable class must be polymorphic. 
 * 2. The class must have a buffer as a member variable. 
 * 3. Through some vulnerability, there must be a way for user input to overwrite parts of the V-Table. 
 * 4. After a virtual function pointer is overwritten, the virtual function must be called.
 **************************************/

class Vulnerability
{
public:
   long buffer[10];
public:
   long get(int i){
      return buffer[i];
   };
   void set(int i, long x){
      buffer[i] = x;
   };
   virtual void safe();
};
void Vulnerability::safe(){
   cout << "SAFE\n";
}

void vtableWorking()
{
   cout << "--------working---------\n";
   Vulnerability test;
   test.set(5, 5000);
   test.safe();
}

void vtableExploit()
{
   cout << "----exploit (spray)-----\n";
   Vulnerability* test = new Vulnerability;
   
   test->set(-1, 0); // overwrites the V-Table pointer with a NULL
   test->safe();
   delete test;
}

void vtableSmash()
{
   cout << "----exploit (smash)-----\n";
   Vulnerability* test = new Vulnerability;
   
   long fakeVTable = (long)dangerous; // A fake V-Table
   
   test->set(-1, (long)&fakeVTable); // overwrites the V-Table pointer with a fake
   test->safe();
   delete test;
}

/****************************************
 * STACK VULNERABILTY
 * 1. There must be a buffer such as an array on the stack.
 * 2. The buffer must be reachable from an external input.
 * 3. The mechanism to fill the buffer from the external.
 *    input must not check for the buffer size.
 * 4. The buffer must be overrun (extend beyond the 
 *    intended limits for the array).
 ****************************************/
string displayCharArray(const char * p)
{
   string output;
   for (int i = 0; i < sizeof(size_t); i++)
       output += string(" ") + (p[i] >= ' ' && p[i] <= 'z' ? p[i] : '.');
   return output;
}

void stackVulnerability(long grades[], int numElements)
{
   long stackPoint = 0;
   long sortedGrades[4];
   for (int i = 0; i < numElements; ++i) 
   {
      sortedGrades[i] = grades[i];
   }

   // Show call stack after changes have been made
   // header for our table. Use these setw() offsets in your table
   cout << '[' << setw(2) << 'i' << ']'
        << setw(15) << "address"
        << setw(20) << "hexadecimal"
        << setw(20) << "decimal"
        << setw(18) << "characters"
        << endl;
   cout << "----+"
        << "---------------+"
        << "-------------------+"
        << "-------------------+"
        << "-----------------+\n";
   for (long j = 20; j >= -4; j--)
   {
      cout << '[' << setw(2) << j << ']'
            << setw(15) << (&stackPoint + j)
            << "  0x" 
            << setw(16) << setfill('0') << hex << *(&stackPoint + j)
            << setw(20) << setfill(' ') << *(&stackPoint + j)
            << setw(18) << displayCharArray((char*) (&stackPoint + j))
            << endl;
   }
}


/**************************************
 * STACK WORKING
 * Call arrayVulnerability() in a way that does
 * not yield unexpected behavior
 *************************************/
void stackWorking()
{
   cout << "------STACK WORKING------\n";
   long grades[4] = {100,95,70,100};
   stackVulnerability(grades, 4);
}

/**************************************
 * STACK EXPLOIT
 * 1. 
 *************************************/
void stackExploit()
{
   cout << "------STACK EXPLOIT------\n";
   long grades[5] = {65,70,0,50, (long) &dangerous};
   stackVulnerability(grades, 5);
}

/* ***************************************************
 * Heap Vulnerability
 * In order for a heap smashing vulnerability to exist, the
 * following conditions must be met:
 *  1) There must be two(2) adjacent heap buffers
 *  2) The first buffer must be reachable through external input
 *  3) The mechanism to fill the buffer from the external input
 *     must not correctly check for the buffer size
 *  4) The second buffer must be released before the first.
 *  5) The first buffer must be overrun (extended beyond the
 *     intended limits of the array).
 * **************************************************/
void heapVulnerability()
{
   //TEST CODE!! NOT COMPLETE!!
   char * buffer1 = new char[4];
   char * buffer2 = new char[4];
   cout << "buffer 1 address is " << &buffer1 << " and value is " << buffer1 << endl;
   cout << "buffer 2 address is " << &buffer2 << " and value is " << buffer2 << endl;
   cout << "enter a string: ";
   cin >> buffer1;
   cout << "buffer 1 address is " << &buffer1 << " and value is " << buffer1 << endl;
   cout << "buffer 2 address is " << &buffer2 << " and value is " << buffer2 << endl;
   delete [] buffer2;
   cout << "buffer1 post delete= " << buffer1 << endl;
   delete [] buffer1;
}

/* ***************************************************
 * Heap Working
 * A function that calls heapVulnerability() in a way
 * that does not yield unexpected behavior.
 * ***************************************************/
void heapWorking()
{
   heapVulnerability();
}

/* **************************************************
 * Heap Exploit
 * For a heap smashing vulnerability to be exploited,
 * the following steps must occur:
 *  1) The attacker must provide more data into the outwardly
 *     facing heap buffer than the buffer is designed to hold.
 *  2) The attacker must know the layout of the Memory Control Block (MCB)
 *     (essentially a linked list) residing just after the buffer.
 *  3) The attacker must provide a new MCB contaning both the location
 *     of the memory overwrite and the new data to be overwritten.
 * *************************************************/
void heapExploit()
{
   heapVulnerability();
}

/* *******************************************
 * Integer Vulnerability
 * In order for an integer overflow to exist the following must exist:
 *  1) There must be a security check represented by an expression.
 *  2) The expression must have the potential for overflow
 *  3) At least one of the numbers used to compute the sentinel must
 *     be reachable through external input. This sentinel is a variable
 *     used to make the security decision from the first requirement.
 * In this function, the number passed is of size_t for display
 * purposes. THe comparison is done by casting the number to an int.
 * ******************************************/
void intVulnerability(size_t numDigits)
{
   //Simulate an actual program rather than something hardcoded
   cout << "Welcome to the HighScore storer!\n";
   cout << "This program will store your high score as a char array\n";
   cout << "How many digits are in your high score? (max = 10)\n";
   //To show that excessive large numbers will overflow
   cout << "You entered " << numDigits << " digits.\n";
   //The casting to int creates the vulnerability, a size_t can hold larger numbers
   if ((int)numDigits < 10)
   {
      cout << "Test Passed! Thanks for your help!\n";
   }
   else
   {
      cout << "Test Failed! You entered too many digits.\n";
   }

   //For extra spacing
   cout << endl;    
}

/* ********************************************
 * Integer Working
 * Calls intVulnerability() in a way that does not
 * yield unexpected behavior
 * ********************************************/
void integerWorking()
{
   //5 < 10, works as expected
   intVulnerability(5);
   // 12 > 10, reject as expected
   intVulnerability(12);
}

/* *******************************************
 * Integer Exploit
 * To explot an integer overflow, the following must happen:
 *  1) Provide input, either a buffer size or a single value, that
 *     is directly or indirectly used in the vulnerable expression.
 *  2) The input must exceed the valid bounds of the data-type,
 *     resulting in an overflow or underflow condition.
 * *******************************************/
void integerExploit()
{
   //This number will overflow an integer and pass the check
   // even though it shouldn't
   intVulnerability(3333333333);
}

/**********************************************
 * ANSI UNICODE CONVERSION
 * 1. There must be a buffer where the basetype is greater than one. 
 * 2. Validation of the buffer must check the size of the buffer rather than the number of elements in the buffer.
 *********************************************/

void ansiVulnerability(int i)
{
   int data[] = {1, 1, 2, 6, 24, 120};
   if(i >= 0 && i < sizeof(data)){
      cout << data[i] << endl;
   }else{
      cout << i << " is out of bounds\n";
   }
}

void ansiWorking()
{
   cout << "--------working---------\n";
   cout << "Input of 3\n";
   ansiVulnerability(3);
   cout << "Input of 30\n";
   ansiVulnerability(30);
}

void ansiExploit()
{
   cout << "--------exploit---------\n";
   cout << "Input of 8\n";
   ansiVulnerability(8);
}

// Displays a menu of vulnerabilities
void displayVulnerabilitiesMenu()
{
   cout << "\nWhat kind of vulnerability would you like demonstrated?\n";
   cout << "------------------------------------------\n";
   cout << "\tArray Index              ---  1\n";
   cout << "\tARC Injection            ---  2\n";
   cout << "\tVTable Spraying          ---  3\n";
   cout << "\tStack Smashing           ---  4\n";
   cout << "\tHeap Spraying            ---  5\n";
   cout << "\tInteger Overflow         ---  6\n";
   cout << "\tANSI-Unicode Conversion  ---  7\n";
   cout << "\tQUIT                     ---  q\n";
   cout << "------------------------------------------\n";
   cout << "--> ";
}
int main()
{
   bool quit = false;
   while(!quit)
   {
      char selection = ' ';
      string input = "";
      displayVulnerabilitiesMenu();
      cin >> input;

      if (input.length() == 1)
         selection = input[0];

      switch (selection)
      {
      case '1':
         arrayWorking();
         arrayExploit();
         break;
      case '2':
         arcWorking();
         arcExploit();
         break;
      case '3':
         vtableWorking();
         vtableSmash();
         vtableExploit();
         break;
      case '4':
         stackWorking();
         stackExploit();
         break;
      case '5':
         heapVulnerability();
         break;
      case '6':
         integerWorking();
         integerExploit();
         break;
      case '7':
         ansiWorking();
         ansiExploit();
         break;
      case 'q':
      case 'Q':
         quit = true;
         break;
      default:
         cout << "Invalid input\n";
      }
   }

   return 0;
}
