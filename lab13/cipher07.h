/********************************************************************
* Header:
*    Implement your cipher here. You can view 'example.h' to see the
*    completed Caesar Cipher example.
********************************************************************/
#ifndef CIPHER07_H
#define CIPHER07_H

#include<array>
#include<sstream>

/********************************************************************
 * CLASS
 *******************************************************************/
class Cipher07 : public Cipher
{
public:
   virtual std::string getPseudoAuth()  { return "Ethan Nelson"; }
   virtual std::string getCipherName()  { return "(Checkerboard) Polybius Square"; }
   virtual std::string getEncryptAuth() { return "Thomas Peck"; }
   virtual std::string getDecryptAuth() { return "Caleb Baird";}
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
      str +=  "Encryption pseudocode\n";
      str += "string plaintext\n";
      str +=  "key = passwordToKey(password)\n";
      str += "the key is a 5x5 or a 5x6 array\n";
      str += "for every letter in plaintext\n";
      str += "for rows in key\n";
      str += "for columns in key\n";
      str += "if letter in the plaintext = grid letter\n";
      str += "encription += row, col\n";

      // The decrypt pseudocode
      str += "Decryption pseudocode\n";
      str +=  "key = passwordToKey(password)\n";
      str += "for every 2 numbers in cipher message\n";
      str += "every word is space seperated so if the first character is a blank space a space will be used and the count will increase by 1\n";
      str += "decoded message += key[row+1][col+1]\n";

      // helper function Password to key
      str +=  "password_to_key pseudocode\n";
      str +=  "passwordToKey(password)\n";
      str +=  "loop through whole password: for (int i = 0; i < password.size(); i++)\n";
      str +=  "    add char to row and couumn\n";
      str +=  "    if the number of columns reached is 5 then go to the next column\n";
      str +=  "    next coulmn\n";
      str +=  "return key\n";

      str +=  "if password was 123451abcde2fghij3lmnop4qrstu5vwxyz\n";
      str +=  "Table\n";
      str +=  "0 12345\n";
      str +=  "1 abcde\n";
      str +=  "2 fghij\n";
      str +=  "3 klmno\n";
      str +=  "4 pqrst\n";
      str +=  "5 uvwxy/z\n";


      return str;
   }

   std::array<char, 30> makeKey(const std::string &password){
      std::array<char, 30> key;
      for(char c = 'A'; c <= 'Z'; c++){
         key[c-'A'] = c;
      }
      key[26] = ' ';
      key[27] = '.';
      key[28] = ',';
      key[29] = '?';

      for(int i = 2; i <= 30; i++){
         int acc = 0;
         for(int j = 0; j < password.size(); j++){
            acc *= 256;
            acc += (unsigned char)password[j];
            acc %= i;
         }
         char temp = key[i-1];
         key[i-1] = key[acc];
         key[acc] = temp;
      }
      return key;
   }
   /**********************************************************
    * ENCRYPT
    * TODO: ADD description
    **********************************************************/
   virtual std::string encrypt(const std::string & plainText,
                               const std::string & password)
   {
      std::stringstream cipherText;
      auto key = makeKey(password);
      for(int i = 0; i < plainText.size(); i++){
         char c = toupper(plainText[i]);
         for(int j = 0; j < 30; j ++){
            if(key[j] == c){
               cipherText << (j/6 + 1);
               cipherText << (j%6 + 1);
            }
         }
      }
      return cipherText.str();
   }

   /**********************************************************
    * DECRYPT :: use the key to lookup the characters
    * represented by each two number pair in cipherText.
    **********************************************************/
   virtual std::string decrypt(const std::string & cipherText,
                               const std::string & password)
   {

      std::string plainText = "";
      auto key = makeKey(password);
      for(int i = 0; i < cipherText.size(); ++i){
         int c1 = cipherText[i] - '0';
         int c2 = cipherText[++i] - '0';
         plainText += key[(c1 - 1) * 6 + (c2 - 1)];
      }
      return plainText;
   }
};

#endif // CIPHER07_H
