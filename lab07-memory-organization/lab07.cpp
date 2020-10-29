#include <iostream>
#include <iomanip>
#include <string>
#include <string.h>
#include <cassert>
using namespace std;

void one(long number);
void two(long number);
void pass() { cout << "You pass :)\n"; }
void fail() { cout << "You've failed :(\n"; }
const char * passMessage = ":)";
const char * failMessage = ":(";

/**********************************************
 * MAIN : The top of the callstack.
 **********************************************/
int main()
{
   char text[8] = "*MAIN**";
   long number = 123456;
   void (*pointerFunction)() = fail;
   const char * message = failMessage;

   // display the initial values of the local variables
   cout << "main() : " << (void *)main << endl;
   cout << "\ttext:             " << text              << endl;
   cout << "\tnumber:           " << number            << endl;
   cout << "\tmessage:          " << message           << endl;
   cout << "\tfunction pointer: ";
   pointerFunction();

   // call the other functions
   one(number + 111111);     // 234567

   // display the new values of the local variables
   cout << "main() - after\n";
   cout << "\ttext:             " << text              << endl;
   cout << "\tnumber:           " << number            << endl;
   cout << "\tmessage:          " << message           << endl;
   cout << "\tfunction pointer: ";
   pointerFunction();

   return 0;
}

/************************************************
 * CONVERT TO STRING
 * Convert the data from p into a human-readable string
 * by removing all the unprintable characters and replacing
 * them with a dot
 ***********************************************/
string displayCharArray(const char * p)
{
   string output;
   for (int i = 0; i < sizeof(size_t); i++)
       output += string(" ") + (p[i] >= ' ' && p[i] <= 'z' ? p[i] : '.');
   return output;
}

/**********************************************
 * ONE : The next item on the call stack
 **********************************************/
void one(long number)               // 234567
{
   char text[8] = "**ONE**";

   cout << "one() : " << (void *)one << endl;
   cout << "\tmessage: " << (void *)failMessage << endl;
   cout << "\tfail():  " << (void *)fail        << endl;

   two(number + 111111);    // 345678
}

/**********************************************
 * TWO : The bottom of the call stack
 **********************************************/

void two(long number)              // 345678
{
   cout << "Check" << endl;
   // start your display of the stack from this point
   size_t bow = number + 111111;     // 456789
   char text[8] = "**TWO**";
   long * pLong = NULL;
   char * pChar = NULL;
   
   int foundText = 0;
   int foundNum = 0;
   int foundFunction = 0;
   int foundCharPointer = 0;
   long i=0;

   while (foundText == 0 ||
            foundNum == 0 ||
            foundFunction == 0 ||
            foundCharPointer == 0) 
   {
      // change text in main() to "*main**"
      pChar = (char *)(&bow + i);
      for (int j = 0; j < sizeof(size_t); j++)
      {
         
         if (!strcmp("*MAIN**", pChar + j))
         {
            strcpy((pChar + j), "*main**"); 
            ++foundText;    
         }
      }
      
      // if (*(&bow + i) == *(size_t*)("*MAIN**"))
      // {
      //    strcpy((char*) (&bow + i), "*main**"); 
      //    ++foundText;    
      // }
      
      // change number in main() to 654321
      if (*(&bow + i) == 123456)
      {
         *(&bow + i) = 654321;
         ++foundNum;
      }

      // change pointerFunction in main() to point to pass
      if (*(&bow + i) == (size_t)&fail)
      {
         *(&bow + i) = (size_t)&pass;
         ++foundFunction;
      }

      // change message in main() to point to passMessage
      if (*(&bow + i) == (size_t)failMessage)
      {
         *(&bow + i) = (size_t)passMessage;
         ++foundCharPointer;
      }

      // increement i
      i++;

      // emergency exit
      if (i>50)
         break;
   }

   

   // Making sure that we have found the specified values exactly once
   //assert(foundText == 1);
   // assert(foundNum == 1);
   // assert(foundFunction == 1);
   // assert(foundCharPointer == 1);


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
   for (long j = i; j >= -4; j--)
   {
      cout << '[' << setw(2) << j << ']'
            << setw(15) << (&bow + j)
            << "  0x" 
            << setw(16) << setfill('0') << hex << *(&bow + j)
            << setw(20) << setfill(' ') << dec << *(&bow + j)
            << setw(18) << displayCharArray((char*) (&bow + j))
            << endl;
   }

   //cout << "size of: " << sizeof(size_t);
}
