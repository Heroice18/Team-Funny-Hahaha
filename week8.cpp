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
   arcVunerability();
}

void arcExploit()
{
   arcVunerability();
}

class Vulnerability
{
};

void vtableWorking()
{
   Vulnerability test;
   test.vunerable();
}

void vtableExploit()
{
   Vulnerability test;
   test.vunerable();
}

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

void intVulnerability()
{
}

void integerWorking()
{
   intVulnerability();
}

void integerExploit()
{
   intVulnerability();
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

int main()
{
   return 0;
}
