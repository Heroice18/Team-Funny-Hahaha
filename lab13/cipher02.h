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
   virtual std::string getEncryptAuth() { return "encrypt author"; }
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

   /**********************************************************
    * ENCRYPT
    * TODO: ADD description
    **********************************************************/
   virtual std::string encrypt(const std::string & plainText,
                               const std::string & password)
   {
      std::string cipherText = plainText;
      // TODO - Add your code here
      return cipherText;
   }

   /**********************************************************
    * DECRYPT
    * TODO: ADD description
    **********************************************************/
   virtual std::string decrypt(const std::string & cipherText,
                               const std::string & password)
   {
      std::string plainText = cipherText;
      // TODO - Add your code here
      return plainText;
   }
};

#endif // CIPHER02_H