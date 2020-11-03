#include <iostream>
using namespace std;

/****************************************
 * ARRAY VULNERABILTY
 * 1. There must be an array and an array index variable
 * 2. The array index variable must be reachable through external input.
 * 3. There must not be bounds checking on the array index variable.
 ****************************************/
void arrayVulnerability(int num)
{
   int array[10] = {1, 1, 2, 3, 5, 8, 13, 21, 34, 55};
   cout << "Which Fibbonacchi number would you like to see?\n";
   cout << "num passed is: " << num << endl;
   cout << "array[" << num - 1 << "] = " << array[num - 1] << endl;
}

/**************************************
 * ARRAY WORKING
 * Call arrayVulnerability() in a way that does
 * not yield unexpected behavior
 *************************************/
void arrayWorking()
{
   arrayVulnerability(5);
}

/**************************************
 * ARRAY EXPLOIT
 * 1. The attacker provides an array index value outside the expected range
 * 2. The attacker must be able to provide input or redirect
 *    existing input into the array at the index he provided
 * 3. The injected value must alter program state in a way
 *    that is desirable to the attacker
 *************************************/
void arrayExploit()
{
   arrayVulnerability(12);
}

void arcVulnerability()
{
}

void arcWorking()
{
   arcVulnerability();
}

void arcExploit()
{
   arcVulnerability();
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

void unsafe(Vulnerability* self){
   cout << "UNSAFE\n";
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
   cout << "------exploit (spraying)--\n";
   Vulnerability* test = new Vulnerability;
   
   test->set(-1, 0);
   test->safe();
   delete test;
}

void vtableSmash()
{
   cout << "--------exploit (smash)---------\n";
   Vulnerability* test = new Vulnerability;
   
   long fakeVTable = (long)unsafe;
   
   test->set(-1, (long)&fakeVTable);
   test->safe();
   delete test;
}

/****************************************
 * STACK VULNERABILTY
 * 1.
 * 2.
 * 3. There must not be bounds checking on the array index variable.
 ****************************************/

void stackVulnerability()
{
}

void stackWorking()
{
   stackVulnerability();
}

void stackExploit()
{
   stackVulnerability();
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
   cout << "enter a string: ";
   cin >> buffer1;
   cout << "buffer1 = " << buffer1 << endl;
   cout << "buffer2 = " << buffer2 << endl;
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
 * ******************************************/
void integerVulnerability(size_t numDigits)
{
   cout << "Welcome to the HighScore storer!\n";
   cout << "This program will store your high score as a char array\n";
   cout << "How many digits are in your high score? (max = 10)\n";
   cout << "You entered " << numDigits << " digits.\n";
   //The casting to int creates the vulnerability
   if ((int)numDigits < 10)
   {
      cout << "Test Passed! Thanks for your help!\n";
   }
   else
   {
      cout << "Test Failed! You entered too many digits.\n";
   }

   cout << endl; //For extra spacing
   
}

/* ********************************************
 * Integer Working
 * Calls integerVulnerability() in a way that does not
 * yield unexpected behavior
 * ********************************************/
void integerWorking()
{
   integerVulnerability(5);
   integerVulnerability(12);
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
   //This number will overflow an integer and appear negative
   integerVulnerability(3333333333);
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
         arcVulnerability();
         break;
      case '3':
         vtableWorking();
         vtableSmash();
         vtableExploit();
         break;
      case '4':
         stackVulnerability();
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
