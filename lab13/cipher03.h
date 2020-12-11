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
   virtual std::string getEncryptAuth() { return "Will Von Doersten"; }
   virtual std::string getDecryptAuth() { return "Brandon Ison"; }

   /***********************************************************
    * GET CIPHER CITATION
    * Returns the citation from which we learned about the cipher
    ***********************************************************/
   virtual std::string getCipherCitation()
   {
      std::string sources;
      sources += "Bellovin, Steven M. (2011). \"Frank Miller: Inventor of the One-Time Pad\". Cryptologia. 35 (3): 203–222.\n";
      sources += "Arisman et al 2019 J. Phys.: Conf. Ser. 1339 012010. \"Enhancement of OTP stream cipher algorithm based on bit separation.\"\n";
      sources += "cryto-it.net (2020). \"http://www.crypto-it.net/eng/symmetric/otp.html.\"\n";
      return std::string(sources);
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
    * Description: This function takes plaintext and a password
    * and encrypts using XOR in a loop to return ciphertext.
    **********************************************************/
   virtual std::string encrypt(const std::string & plainText,
                               const std::string & password)
   {
      std::string cipherText = plainText;
      size_t sizeText = cipherText.size();

      for (size_t i = 0; i < sizeText; i++)
         cipherText[i] = (short int) plainText[i] ^ (short int) password[i];
      
      return cipherText;
   }

   /**********************************************************
    * DECRYPT Brandon Ison
    * TODO: ADD description
    **********************************************************/
   virtual std::string decrypt(const std::string & cipherText,
                               const std::string & password)
   {
      std::string plainText = cipherText;

      size_t sizeText = plainText.size();

      for (size_t i = 0; i < sizeText; i++)
      {
         plainText[i] = (short int) cipherText[i] ^ (short int) password[i];
      }
        
      
      return plainText;
   }
};

#endif // CIPHER03_H