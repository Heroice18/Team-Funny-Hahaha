#include <iostream>
using namespace std;

/****************************************
 * ARRAY VULNERABILTY
 * 1. There must be an array and an array index variable
 * 2. The array index variable must be reachable through external input.
 * 3. There must not be bounds checking on the array index variable.
 ****************************************/
void arrayVulnerability(/* feel free to add parameters */)
{
}

/**************************************
 * ARRAY WORKING
 * Call arrayVulnerability() in a way that does
 * not yield unexpected behavior
 *************************************/
void arrayWorking()
{
   arrayVulnerability(/* parameters with non-malicious data */);
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
   arrayVulnerability(/* parameters with malicious data */);
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

class Vulnerability
{
};

void vtableWorking()
{
   Vulnerability test;
   // test.vunerable();
}

void vtableExploit()
{
   Vulnerability test;
   // test.vunerable();
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

void heapVulnerability()
{
}

void heapWorking()
{
   heapVulnerability();
}

void heapExploit()
{
   heapVulnerability();
}

void integerVulnerability()
{
}

void integerWorking()
{
   integerVulnerability();
}

void integerExploit()
{
   integerVulnerability();
}

void ansiVulnerability()
{
}

void ansiWorking()
{
   ansiVulnerability();
}

void ansiExploit()
{
   ansiVulnerability();
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
         arrayVulnerability();
         break;
      case '2':
         arcVulnerability();
         break;
      case '3':
         // vtableVulnerability();
         break;
      case '4':
         stackVulnerability();
         break;
      case '5':
         heapVulnerability();
         break;
      case '6':
         integerVulnerability();
         break;
      case '7':
         ansiVulnerability();
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
