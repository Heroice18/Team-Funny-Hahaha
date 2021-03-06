/********************************************************************
* Header:
*    Implement your cipher here. You can view 'example.h' to see the
*    completed Caesar Cipher example.
********************************************************************/
#ifndef CIPHER05_H
#define CIPHER05_H

/********************************************************************
 * CLASS
 *******************************************************************/
class Cipher05 : public Cipher
{
public:
   virtual std::string getPseudoAuth()  { return "Caleb Baird"; }
   virtual std::string getCipherName()  { return "Beaufort Cipher"; }
   virtual std::string getEncryptAuth() { return "Tyler Peart"; }
   virtual std::string getDecryptAuth() { return "Jonathan Hald"; }

   /***********************************************************
    * GET CIPHER CITATION
    * Returns the citation from which we learned about the cipher
    ***********************************************************/
   virtual std::string getCipherCitation()
   {
      std::string s;
      s += "cryto-it.net (2020), ";
      s += "Beaufort Cipher - POLYALPHABETIC SUBSTITUTION CIPHER, \n";
      s += "retrieved: ";
      s += "http://www.crypto-it.net/eng/simple/beaufort-cipher.html";
      return s;
   }

   /**********************************************************
    * GET PSEUDOCODE
    * Returns the pseudocode as a string to be used by the caller.
    **********************************************************/
   virtual std::string getPseudocode()
   {
      std::string str;

      // The encrypt pseudocode
      str =  "";
      str += "-------------------------------------------------------\n";
      str += " Beaufort Cipher -- HINT this is a reciprocal cipher\n";
      str += "       so encrypt and decrypt functions are the same\n";
      str += "-------------------------------------------------------\n";
      str += " FUNCTION encypt(key, plainText)\n";
      str += "    cipherText <- \"\"\n";
      str += "    pos <- 0\n";
      str += "    plainTextLengh <- # letters in plainText\n";
      str += "\n";
      str += "    FOR pos < plainTextLength DO\n";
      str += "       letterRow <- ' '\n";
      str += "       plainTextLetter <- plainText[pos]\n";
      str += "\n";
      str += "       WHILE plainTextLetter != key[pos % len(key)] DO\n";
      str += "          plainTextLetter <- (plainTextLetter - ' ' + 1)";
      str += " MOD 95 + ' '\n";
      str += "          letterRow <- (letterRow - ' ' + 1) MOD 95 + ' '\n";
      str += "       END WHILE\n";
      str += "\n";
      str += "       cipherText += letterRow\n";
      str += "       pos += 1\n";
      str += "    END FOR\n";
      str += "\n";
      str += "    RETURN cipherText\n";
      str += " END FUNCTION\n\n";

      // The decrypt pseudocode
      str += " FUNCTION encypt(key, cipherText)\n";
      str += "    plainText <- \"\"\n";
      str += "    pos <- 0\n";
      str += "    cipherTextLengh <- # letters in cipherText\n";
      str += "\n";
      str += "    FOR pos < cipherTextLength DO\n";
      str += "       letterRow <- ' '\n";
      str += "       cipherTextLetter <- cipherText[pos]\n";
      str += "\n";
      str += "       WHILE cipherTextLetter != key[pos % len(key)] DO\n";
      str += "          cipherTextLetter <- (cipherTextLetter - ' ' + 1)";
      str += " MOD 95 + ' '\n";
      str += "          letterRow <- (letterRow - ' ' + 1) MOD 95 + ' '\n";
      str += "       END WHILE\n";
      str += "\n";
      str += "       plainText += letterRow\n";
      str += "       pos += 1\n";
      str += "    END FOR\n";
      str += "\n";
      str += "    RETURN plainText\n";
      str += " END FUNCTION\n";

      return str;
   }

   /**********************************************************
    * ENCRYPT
    * TODO: ADD description
    **********************************************************/
   virtual std::string encrypt(const std::string & plainText,
                               const std::string & password)
   {
      std::string cipherText = "";
      int ptLength = plainText.length();
      int pwdLength = password.length();

      for (int pos = 0; pos < ptLength; ++pos)
      {
         char letterRow = ' ';
         char ptLetter = plainText[pos];
         while (ptLetter != password[pos % pwdLength])
         {
            ptLetter = (ptLetter - ' ' + 1) % 95 + ' ';
            letterRow = (letterRow - ' ' + 1) % 95 + ' ';
         }
         cipherText += letterRow;
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
      std::string plainText = "";
      int cipherTextLength = cipherText.length();
      for (int pos = 0; pos < cipherTextLength; ++pos)
      {
         char letterRow = ' ';
         char cipherTextLetter = cipherText[pos];
         while (cipherTextLetter != password[pos % password.length()])
         {
            cipherTextLetter = (cipherTextLetter - ' ' + 1) % 95 + ' ';
            letterRow = (letterRow - ' ' + 1) % 95 + ' ';
         }
         plainText += letterRow;
      }

      return plainText;
   }
};

#endif // CIPHER05_H
