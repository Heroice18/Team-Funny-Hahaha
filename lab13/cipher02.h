/********************************************************************
* Header:
*    Implement your cipher here. You can view 'example.h' to see the
*    completed Caesar Cipher example.
********************************************************************/
#ifndef CIPHER02_H
#define CIPHER02_H

/********************************************************************
 * CLASS
 *******************************************************************/
class Cipher02 : public Cipher
{
public:
   virtual std::string getPseudoAuth()  { return "Will Von Doersten"; }
   virtual std::string getCipherName()  { return "RC4 Cipher"; }
   virtual std::string getEncryptAuth() { return "Brandon Ison"; }
   virtual std::string getDecryptAuth() { return "Ethan Nelson"; }

   /***********************************************************
    * GET CIPHER CITATION
    * Returns the citation from which we learned about the cipher
    ***********************************************************/
   virtual std::string getCipherCitation()
   {
      std::string sources;

      sources += "Wikipedia.com, ";
      sources += " RC4 Cipher,\n   retrieved: 9 DEC 2020\n";
      sources += "https://en.wikipedia.org/wiki/RC4\n";

      sources += "Chris Kowalczyk, ";
      sources += " RC4,\n   retrieved: 9 DEC 2020\n";
      sources += "http://www.crypto-it.net/eng/symmetric/rc4.html\n";

      return sources;
   }
   
   /**********************************************************
    * GET PSEUDOCODE
    * Returns the pseudocode as a string to be used by the caller.
    **********************************************************/
   virtual std::string getPseudocode()
   {
      std::string str;

      // Helper create table function
      str += "createTable(tTable, key, keyLen)\n";
      str += "   for i from 0 to 255\n";
      str += "      tTable[i] <- i\n";
      str += "   temp <- 0\n";
      str += "   for i from 0 to 255\n";
      str += "      temp <- (temp + T[i] + key[i mod keyLen]) mod 256\n";
      str += "      swap(T[i], T[temp])\n";

      // The encrypt pseudocode
      str += "encryptMsg(tTable, plainText, key)\n";
      str += "   for n from length plainText to end\n";
      str += "      i <- (i + 1) mod 256\n";
      str += "      j <- (j + tTable[i]) mod 256\n";
      str += "      swap(&tTable[i], &tTable[j])\n";
      str += "      sum <- tTable[(tTable[i] + tTable[j]) % N]\n";
      str += "      cipherText <- sum XOR plainText[n]\n";
      str += "   RETURN cipherText\n";

      // The decrypt pseudocode
      str += "decryptMsg(tTable, cipherText, key)\n";
      str += "   for n from length cipherText to end\n";
      str += "      i <- (i + 1) mod 256\n";
      str += "      j <- (j + tTable[i]) mod 256\n";
      str += "      swap(&tTable[i], &tTable[j])\n";
      str += "      sum <- tTable[(tTable[i] + tTable[j]) % N]\n";
      str += "      plainText <- sum XOR cipherText[n]\n";
      str += "   RETURN plainText\n";

      return str;
   }

   char tTable[255];
   int mod256 = 256;

   /**********************************************************
    * Helper   Brandon Ison
    * TODO: The createTable function fille the tTable. The tTable
    *  is the encryption table which we use to schedule the iterations
    *  of the key as we encrypt/decrypt the text.
    **********************************************************/
   virtual void createTable(const std::string & password)
   {
      
      int keyLen = password.length();
      for (int i = 0; i < 255; i++)
      {
         tTable[i] = i;
      }
      
      int temp = 0;

      for (int i = 0; i < 255; i++)
      {
         temp = (temp + tTable[i] + password[i % keyLen]) % mod256;
         std::swap(tTable[i], tTable[temp]);
      }
   
   }

   /**********************************************************
    * ENCRYPT  Brandon Ison
    * TODO: The encrypt function takes in a plaintext and a password
    * and returns the encrypted text. We create the tTable using the createTable
    * function and passing in the password. 
    **********************************************************/
   virtual std::string encrypt(const std::string & plainText,
                               const std::string & password)
   {
      std::string cipherText = plainText;
      //fill the tTable with the iterations for the key
      createTable(password);

      int i = 0;
      int j = 0;

      //loop through the plaintext and convert the characters into ciphertext using the tTable
      for(int n =0; n <= plainText.length(); n++)
      {
         i = (i+1) % mod256;
         j = (j + tTable[i]) % mod256;

         std::swap(tTable[i], tTable[j]);
         int sum = tTable[(tTable[i] + tTable[j]) % mod256];

         cipherText[n] = sum ^ plainText[n];

      }

      return cipherText;
   }

   /**********************************************************
    * DECRYPT
    * TODO: ADD description
    **********************************************************/
   virtual std::string decrypt(const std::string & cipherText,
                               const std::string & password)
   {
      // set up used variables
      createTable(password);
      int i=0;
      int j=0;
      std::string plainText;

      // loop for all of the characters in the cipher text
      for(int n; n < cipherText.length(); n++)
      {
         i = (i+1) % 256;
         j=(j+tTable[i]) % 256;

         std::swap(tTable[i], tTable[j]);
         int sum = tTable[(tTable[i] + tTable[j]) % n];

         plainText[n] = sum ^ cipherText[n];
      }

      return plainText;
   }
};

#endif // CIPHER02_H