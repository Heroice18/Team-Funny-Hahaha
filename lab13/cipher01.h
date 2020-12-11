/********************************************************************
* Header:
*    Implement your cipher here. You can view 'example.h' to see the
*    completed Caesar Cipher example.
*     Done by Brandon Ison
********************************************************************/
#ifndef CIPHER01_H
#define CIPHER01_H

/********************************************************************
 * CLASS
 *******************************************************************/
class Cipher01 : public Cipher
{
public:
   virtual std::string getPseudoAuth()  { return "Brandon Ison"; }
   virtual std::string getCipherName()  { return "Vigenère Cipher"; }
   virtual std::string getEncryptAuth() { return "Ethan Nelson"; }
   virtual std::string getDecryptAuth() { return "Brandon Ison"; }

   /***********************************************************
    * GET CIPHER CITATION
    * Returns the citation from which we learned about the cipher
    ***********************************************************/
   virtual std::string getCipherCitation()
   {
      std::string sources;
      sources += "How much do you know about the Vigenere cipher?\n";
      sources += "\t https://community.ibm.com/community/user/ibmz-and-linuxone/blogs/subhasish-sarkar1/2020/07/17/how-much-do-you-know-about-the-vigenere-cipher \n";
      sources += "Cryptography, Information Theory, and Error-Correction\n";
      sources += "\t https://books.google.com/books?id=fd2LtVgFzoMC&pg=PA21#v=onepage&q&f=false"; 
      return sources;
   }
   
   /**********************************************************
    * GET PSEUDOCODE
    * Returns the pseudocode as a string to be used by the caller.
    **********************************************************/
   virtual std::string getPseudocode()
   {
      std::string codeP;


       // The helper function
      codeP = "createKey(plaintext, key)\n";
      // Get the size of the plaintext so we can make the size of the key match
      codeP += "  sizeV <- plaintext.size() \n";
      //For loop going through and editing the key
      codeP += "  FOR i = 0; i++\n";
      codeP += "     IF sizeV == i\n";
      // resets the i integer so that the key can loop back around
      codeP += "        i = 0\n";
      // Check to see if the plaintext and the key size are the same
      codeP += "     IF plaintext.size() == key.size()\n";
      codeP += "        RETURN key\n";
      codeP += "     key += key at i\n";
      codeP += "\n";
      
      // The encrypt pseudocode
      codeP +=  "encryptV(plaintext, key)\n";
      codeP += "  encryptKey <- createKey(plaintext, key)\n";
      codeP += "  encryptedText <- empty()\n";
      codeP += "  FOR i is all values in plaintext\n";
      //To find the location in the alphabet that the key is at
      codeP += "     encryptIndex = (plaintext[i] + encryptKey[i] +26) %26 \n";
      //Convert int to ASCII
      codeP += "     encryptIndex = encryptIndex + 'A'\n";
      codeP += "     encryptedText += encryptIndex\n";
      codeP += "  RETURN encryptedText\n";
      codeP += "\n";
      
      // The decrypt pseudocode
      codeP += "decryptV(plaintext, key)\n";
      codeP += "  decryptKey <- createKey(plaintext, key)\n";
      codeP += "  decryptedText <- empty()\n";
      codeP += "  FOR i is all values in plaintext\n";
      //To find the location in the alphabet that the key is at
      codeP += "     decryptIndex = (plaintext[i] - decryptKey[i] +26) %26 \n";
      //Convert int to ASCII
      codeP += "     decryptIndex = decryptIndex + 'A'\n";
      codeP += "     decryptedText += decryptIndex\n";
      codeP += "  RETURN decryptedText\n";
      codeP += "\n";

      return codeP;
   }

   /**********************************************************
    * CREATE_KEY (Ethan Nelson)
    * Create Key creates the key that is to be used during the
    * encryption process
    **********************************************************/
   virtual std::string createKey(const std::string plainText, 
                               std::string key)
   {
      // get the size of the plaintext being used
      int sizeV = plainText.size();
      // loop forever (until the plaintext and key sizes are the same)
      for(int i = 0;  ; i++)
      {
         // resets the loop
         if(sizeV == i)
            i = 0;

         // checks to see if the plaintext and key are the same
         if(plainText.size() == key.size())
            return key;

         key.push_back(key[i]);
      }
   }
   /**********************************************************
    * ENCRYPT
    * TODO: ADD description
    **********************************************************/
   virtual std::string encrypt(const std::string & plainText, 
                               const std::string & password)
   {
      // Set up variables
      std::string encryptKey = createKey(plainText, password);
      std::string encryptedText;

      // loop through the plaintext
      for(int i = 0; i < plainText.size(); i++)
      {
         // find the location in the alphabet the key is at
         char encryptIndex = (plainText[i] + encryptKey[i]) % 26;
         // convert to ASCII
         encryptIndex += 'A';
         encryptedText.push_back(encryptIndex);
      }

      return encryptedText;
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

#endif // CIPHER01_H