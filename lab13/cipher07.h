/********************************************************************
* Header:
*    Implement your cipher here. You can view 'example.h' to see the
*    completed Caesar Cipher example.
********************************************************************/
#ifndef CIPHER07_H
#define CIPHER07_H

/********************************************************************
 * CLASS
 *******************************************************************/
class Cipher07 : public Cipher
{
public:
   virtual std::string getPseudoAuth()  { return "Ethan Nelson"; }
   virtual std::string getCipherName()  { return "(Checkerboard) Polybius Square"; }
   virtual std::string getEncryptAuth() { return "Ethan Nelson"; }
   virtual std::string getDecryptAuth() { return "Ethan Nelson"; }

   /***********************************************************
    * GET CIPHER CITATION
    * Returns the citation from which we learned about the cipher
    ***********************************************************/
   virtual std::string getCipherCitation()
   {
      return std::string("https://www.cryptogram.org/downloads/aca.info/ciphers/Checkerboard.pdf \n https://crypto.interactive-maths.com/polybius-square.html \n https://www.geeksforgeeks.org/polybius-square-cipher/");
   }
   
   /**********************************************************
    * GET PSEUDOCODE
    * Returns the pseudocode as a string to be used by the caller.
    **********************************************************/
   virtual std::string getPseudocode()
   {
      std::string str;

      // The encrypt pseudocode
      str =  "Encryption pseudocode\n";
      str += "for rows in grid\n";
      str += "for columns in grid\n";
      str += "if letter to be encrypted = grid letter\n";
      str += "encription += row, col\n";



      // The decrypt pseudocode
      str += "Decryption pseudocode\n";
      str += "for every 2 numbers in encoded message\n";
      str += "decoded message += grid[row][col]\n";
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

#endif // CIPHER07_H