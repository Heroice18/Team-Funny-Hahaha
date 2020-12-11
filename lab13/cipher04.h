/********************************************************************
* Header:
*    Implement your cipher here. You can view 'example.h' to see the
*    completed Caesar Cipher example.
********************************************************************/
#ifndef CIPHER04_H
#define CIPHER04_H
#include "sha256.h"


/********************************************************************
 * CLASS
 *******************************************************************/
class Cipher04 : public Cipher
{
public:
   virtual std::string getPseudoAuth()  { return "Tyler Peart"; }
   virtual std::string getCipherName()  { return "Salsa20"; }
   virtual std::string getEncryptAuth() { return "Jonathan Hald"; }
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

      //helper function
      str ="generateInitialState(key, nonce, pos)\n";
      //Each index of out is a 32 bit integer
      str+="   out[0] <- 1702391905\n";  //"expa" in decimal
      //Split the 128 bit key into 4 indicies
      str+="   out[1-4] <- key\n";
      str+="   out[5] <- 1852055603\n";  //"nd 3" in decimal
      //Split the 64 bit nonce into 4 indicies
      str+="   out[6-7] <- nonce\n";
      //pos relates to a section of 512 bits.
      str+="   out[8-9] <- pos\n"; //for simplicity we can just use zeros
      str+="   out[10] <- 841835129\n";  //"2-by" in decimal
      //A repeat of out[1-4]
      str+="   out[11-14] <- key\n";
      str+="   out[15] <- 1952784491\n"; //"te k" in decimal
      str+="   RETURN out\n";

      //Helper function
      str+="uint32 ROTL(a, b)\n";
      str+="   x <- a LEFTSHIFT b\n";
      str+="   y <- a RIGHTSHIFT (32 - b)\n";
      str+="   RETURN x BIT-OR y\n";

      //Helper function
      str+="QR(a, b, c, d)\n";
      str+="   b BIT-XOR ROTL(a + d, 7)\n";
      str+="   c BIT-XOR ROTL(b + a, 9)\n";
      str+="   d BIT-XOR ROTL(c + b, 13)\n";
      str+="   a BIT-XOR ROTL(d + c, 18)\n";

      //helper function that genarates 512 bits of cipher
      str+="salsa20(out, in)\n";
      str+="   LOOP for i FROM 0 to 16\n";
      str+="      x[i] <- in[i]\n";
      str+="   LOOP 10 times\n";
      //rotations along the columns
      str+="      QR(x[0], x[4], x[8], x[12])\n";
      str+="      QR(x[5], x[9], x[13], x[1])\n";
      str+="      QR(x[10], x[14], x[2], x[6])\n";
      str+="      QR(x[15], x[3], x[7], x[11])\n";
      //rotations along the rows
      str+="      QR(x[0], x[1], x[2], x[3])\n";
      str+="      QR(x[5], x[6], x[7], x[4])\n";
      str+="      QR(x[10], x[11], x[8], x[9])\n";
      str+="      QR(x[15], x[12], x[13], x[14])\n";
      str+="   LOOP for i FROM 0 to 16\n";
      str+="      out[1] <- x[i] + in[i]\n";

      //a helper function
      str+="void convertPassword(password,int32 &key,int32 &nonce)\n";
      str+="   string hash <- sha256(password)\n";
      //make a 32 bit key and a nonce from the hash
      str+="   key = stoi (hash.substr(0,7), nullptr, 16)\n";
      str+="   nonce = stoi (hash.substr(0,7), nullptr, 16)\n";
      str+="   RETURN key, nonce\n";
      // The encrypt pseudocode
      str+="encrypt(plaintext, password)\n";
      str+="   convertPassword(password,key,nonce)\n";
      str+="   in <- generateInitialState(key, nonce, 0)\n";
      str+="   salsa20(out, in)\n";
      str+="   RETURN plaintext BIT-XOR out\n";

      // The decrypt pseudocode
      str+="decrypt(ciphertext, password)\n";
      str+="   convertPassword(password,key,nonce)\n";
      str+="   in <- generateInitialState(key, nonce, 0)\n";
      str+="   salsa20(out, in)\n";
      str+="   RETURN ciphertext BIT-XOR out\n";

      return str;
   }

   uint32_t * generateInitialState(uint32_t key,uint32_t nonce, uint32_t pos)
   {
      uint32_t out[16];
      out[0] = 1702391905;
      out[1] = key;
      out[2] = key;
      out[3] = key;
      out[4] = key;
      out[5] = 1852055603;
      out[6] = nonce;
      out[7] = nonce;
      out[8] = pos;
      out[9] = pos;
      out[10] = 841835129;
      out[11] = key;
      out[12] = key;
      out[13] = key;
      out[14] = key;
      out[15] = 1952784491;

      return out;
   }

   uint32_t ROTL(uint32_t a, uint32_t b)
   {
      (((a) << (b)) | ((a) >> (32 - (b))));
   }

   void QR(uint32_t a, uint32_t b, uint32_t c, uint32_t d)
   {
      (b ^= ROTL(a + d, 7),	
	    c ^= ROTL(b + a, 9),	
	    d ^= ROTL(c + b,13),	
	    a ^= ROTL(d + c,18));
   }

   void salsa20(uint32_t out[16], uint32_t const in[16])
   {
      int i;
	   uint32_t x[16];

	   for (i = 0; i < 16; ++i)
      {
		   x[i] = in[i];
      }
	   for (i = 0; i < 10; i += 2) 
      {
		   QR(x[ 0], x[ 4], x[ 8], x[12]);
		   QR(x[ 5], x[ 9], x[13], x[ 1]);
		   QR(x[10], x[14], x[ 2], x[ 6]);	
		   QR(x[15], x[ 3], x[ 7], x[11]);	
	
		   QR(x[ 0], x[ 1], x[ 2], x[ 3]);
		   QR(x[ 5], x[ 6], x[ 7], x[ 4]);
		   QR(x[10], x[11], x[ 8], x[ 9]);	
		   QR(x[15], x[12], x[13], x[14]);
	   }
	   for (i = 0; i < 16; ++i)
      {
		   out[i] = x[i] + in[i];
      }
   }

   void convertPassword(std::string password, uint32_t & key, uint32_t & nonce)
   {
      std::string hash = sha256(password);
      key = stoi(hash.substr(0,7), nullptr, 16);
      nonce = stoi(hash.substr(0,7), nullptr, 16);
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
      uint32_t key;
      uint32_t nonce;
      uint32_t out[16];
      convertPassword(password, key, nonce);
      uint32_t * in = generateInitialState(key, nonce, 0);
      salsa20(out, in);



      return cipherText/*cipherText ^ out[0]*/;
   }

   /**********************************************************
    * DECRYPT
    * TODO: ADD description
    **********************************************************/
   virtual std::string decrypt(const std::string & cipherText,
                               const std::string & password)
   {
      // std::string plainText = cipherText;
      
   }
};

#endif // CIPHER04_H
