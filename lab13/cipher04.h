/********************************************************************
* Header:
*    Implement your cipher here. You can view 'example.h' to see the
*    completed Caesar Cipher example.
********************************************************************/
#ifndef CIPHER04_H
#define CIPHER04_H

/********************************************************************
 * CLASS
 *******************************************************************/
class Cipher04 : public Cipher
{
public:
   virtual std::string getPseudoAuth()  { return "Tyler Peart"; }
   virtual std::string getCipherName()  { return "Salsa20"; }
   virtual std::string getEncryptAuth() { return "encrypt author"; }
   virtual std::string getDecryptAuth() { return "decrypt author"; }

   /***********************************************************
    * GET CIPHER CITATION
    * Returns the citation from which we learned about the cipher
    ***********************************************************/
   virtual std::string getCipherCitation()
   {
      std::string s;
      s = "Wikipedia.com, ";
      s += "\"Salsa20,\n   retrieved: 8 DEC 2020";
      s += "https://en.wikipedia.org/wiki/Salsa20\n";

      s += "Paper on Salsa20, ";
      s += "\"The Salsa20 family of stream ciphers,\n  retrieved: 8 DEC 2020";
      s += "https://cr.yp.to/snuffle/salsafamily-20071225.pdf";
      return s;
   }
   
   /**********************************************************
    * GET PSEUDOCODE
    * Returns the pseudocode as a string to be used by the caller.
    **********************************************************/
   virtual std::string getPseudocode()
   {
      std::string str;

      //heler functions
      str ="generateInitialState(key, nonce, pos)\n";
      str+="   out[0] <- \"expa\"\n";
      str+="   out[1-4] <- key\n";
      str+="   out[5] <- \"nd 3\"\n";
      str+="   out[6-7] <- nonce\n";
      str+="   out[8-9] <- pos\n";
      str+="   out[10] <- \"2-by\"\n";
      str+="   out[11-14] <- key\n";
      str+="   out[15] <- \"te k\"\n";
      str+="   RETURN out\n";

      str+="ROTL(a, b)\n";
      str+="    x <- a LEFTSHIFT b\n";
      str+="    y <- a RIGHTSHIFT (32 - b)\n";
      str+="    RETURN x BIT-OR y\n";

      str+="QR(a, b, c, d)\n";
      str+="   b BIT-AND ROTL(a + d, 7)\n";
      str+="   c BIT-AND ROTL(b + a, 9)\n";
      str+="   d BIT-AND ROTL(c + b, 13)\n";
      str+="   a BIT-AND ROTL(d + c, 18)\n";

      str+="salsa20(out, in)\n";
      str+="   LOOP for i FROM 0 to 16\n";
      str+="      x[i] <- in[i]\n";
      str+="   LOOP for 10 times\n";
      str+="      QR(x[0], x[4], x[8], x[12])\n";
      str+="      QR(x[5], x[9], x[13], x[1])\n";
      str+="      QR(x[10], x[14], x[2], x[6])\n";
      str+="      QR(x[15], x[3], x[7], x[11])\n";

      str+="      QR(x[0], x[1], x[2], x[3])\n";
      str+="      QR(x[5], x[6], x[7], x[4])\n";
      str+="      QR(x[10], x[11], x[8], x[9])\n";
      str+="      QR(x[15], x[12], x[13], x[14])\n";
      str+="   LOOP for i FROM 0 to 16\n";
      str+="      out[1] <- x[i] + in[i]\n";

      // The encrypt pseudocode
      str+="encrypt(plaintext, key, nonce)\n";
      str+="    in <- generateInitialState(key, nonce, 0)\n";
      str+="    salsa20(out, in)\n";
      str+="    RETURN plaintext BIT-XOR out\n";

      // The decrypt pseudocode
      str+="decrypt(ciphertext, key, nonce, pos)\n";
      str+="    in <- generateInitialState(key, nonce, pos)\n";
      str+="    salsa20(out, in)\n";
      str+="    RETURN ciphertext BIT-XOR out\n";

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

#endif // CIPHER04_H
