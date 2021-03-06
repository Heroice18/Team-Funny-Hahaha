#include <iostream>
#include <iomanip>
#include <string.h>
#include <cassert>
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
int stackVulnerability(long input[], int numElements)
{
   int indexOfHighestGrade = 0;

   // Requirement 1: buffer.
   long grades[10];

   // Requirement 3: There is no check on numElements
   for (int i = 0; i < numElements; i++)
   {
      // Requirements 2: input reaches buffer
      // Requirements 4: when i exceeds 9 the buffer is overrun.
      grades[i] = input[i];
      if (grades[i] > grades[indexOfHighestGrade])
      {
         indexOfHighestGrade = i;
      }
   }
   return indexOfHighestGrade;
}


/**************************************
 * STACK WORKING
 * Call arrayVulnerability() in a way that does
 * not yield unexpected behavior.
 * In this example the stackVulnurability's true
 * purpose is to find the index of the highest
 * grade in the provided buffer.
 *************************************/
void stackWorking()
{
   cout << "------STACK WORKING------\n";
   long grades[10] = {95,70,99,50,100,0,10,75,98,95};
   int indexOfHighestGrade = stackVulnerability(grades, 10);
   cout << "The index of the highest grade is "
        << indexOfHighestGrade << endl;
}

/**************************************
 * STACK EXPLOIT
 * 1. The attacker provides an array index value outside the expected range
 * 2. The attacker must be able to provide input or redirect existing input
 *    into the array at the index he provided.
 * 3. The last element of the array (the one that will overwrite the return address)
 *    is the address of the function "dangerous".
 *************************************/
void stackExploit()
{
   cout << "------STACK EXPLOIT------\n";
   long grades[14] = {12,12,12,12,12,12,12,12,12,12,12,12,12, (long) &dangerous};
   stackVulnerability(grades, 14);
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
void heapVulnerability(char * input)
{
   // Initiating new buffers
   char * buffer1 = new char[4];
   char * buffer2 = new char[4];

   // fill buffer1 from input variable without bounds checking
   strcpy(buffer1, input);

   cout << "\nbuffer1 = " << buffer1 << endl;

   // Deleting buffers 2 then 1
   delete [] buffer2;
   delete [] buffer1;
}

/* ***************************************************
 * Heap Working
 * A function that calls heapVulnerability() in a way
 * that does not yield unexpected behavior.
 * ***************************************************/
void heapWorking()
{
   //Fits within the buffer size, no problems
   heapVulnerability((char *)"Safe");
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
   //Exceeds the buffer size and causes problems
   heapVulnerability((char *)"Pink fluffy unicorns dancing on rainbows -- 10 hour version.");
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
         heapWorking();
         heapExploit();
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
