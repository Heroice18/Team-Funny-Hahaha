/********************************************************************
* Header:
*    Implement your cipher here. You can view 'example.h' to see the
*    completed Caesar Cipher example.
********************************************************************/
#ifndef CIPHER03_H
#define CIPHER03_H

/********************************************************************
 * CLASS
 *******************************************************************/
class Cipher03 : public Cipher
{
public:
   virtual std::string getPseudoAuth()  { return "Jonathan Hald"; }
   virtual std::string getCipherName()  { return "One-Time Pad"; }
   virtual std::string getEncryptAuth() { return "encrypt author"; }
   virtual std::string getDecryptAuth() { return "decrypt author"; }

   /***********************************************************
    * GET CIPHER CITATION
    * Returns the citation from which we learned about the cipher
    ***********************************************************/
   virtual std::string getCipherCitation()
   {
      return std::string("citation");
   }
   
   /**********************************************************
    * GET PSEUDOCODE
    * Returns the pseudocode as a string to be used by the caller.
    **********************************************************/
   virtual std::string getPseudocode()
   {
      std::string str;

      // TODO: please format your pseudocode
      // The encrypt pseudocode
      str += "encryption pseudocode\n";
      str += "size_t len -> plainText size < password size ? plainText size : password size\n";
      str += "int lenDifference -> plainText size - password size\n";
      str += "cipherText resize (len + lenDifference, 'x')\n";
      str += "for size_t i -> 0, i < len, increment i\n";
      str += "cipherText[i] -> short int plainText[i] ^ short int password[i]\n";


      // The decrypt pseudocode
      str += "decryption pseudocode\n";
      str += "size_t len -> cipherText size\n";
      str += "for size_t i -> 0, i < len, increment i\n";
      str += "plainText[i] -> short int cipherText[i] ^ short int password[i]\n";

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
      
   }
};

#endif // CIPHER03_H