/********************************************************************
* Header:
*    Implement your cipher here. You can view 'example.h' to see the
*    completed Caesar Cipher example.
********************************************************************/
#ifndef CIPHER06_H
#define CIPHER06_H

/********************************************************************
 * CLASS
 *******************************************************************/
class Cipher06 : public Cipher
{
public:
   virtual std::string getPseudoAuth()  { return "Thomas Peck"; }
   virtual std::string getCipherName()  { return "Columnar Transposition"; }
   virtual std::string getEncryptAuth() { return "encrypt author"; }
   virtual std::string getDecryptAuth() { return "Tyler Peart"; }

   /***********************************************************
    * GET CIPHER CITATION
    * Returns the citation from which we learned about the cipher
    ***********************************************************/
   virtual std::string getCipherCitation()
   {
      std::string citation;
      citation += "http://www.crypto-it.net/eng/simple/columnar-transposition.html";
      return citation;
   }
   
   /**********************************************************
    * GET PSEUDOCODE
    * Returns the pseudocode as a string to be used by the caller.
    **********************************************************/
   virtual std::string getPseudocode()
   {
      std::string str;

      str =  "encrypt(plaintext, key)\n";
      str += "  vector<string> matrix\n";
      str += "  for 0 <= i < key.length\n";
      str += "    matrix[i] = \"\"\n";
      str += "  for 0 <= i < plaintext.length\n";
      str += "    matrix[i % key.length] += plaintext[i]\n";
      str += "  numkey = numbersFromKey(key)\n";
      str += "  result = \"\"\n";
      str += "  for 0 <= i < numkey.length\n";
      str += "    result += matrix[i]\n";
      str += "  return result\n\n";

      str =  "numbersFromKey(key)\n";
      str += "  vector<pair<char, int>> pairs\n";
      str += "  for 0 <= i < key.length\n"; 
      str += "    pairs[i] = pair(key[i], i)\n";
      str += "  stable_sort(pairs.begin, pairs.end, [](a,b){return a.get<0>() < b.get<0>();})\n";
      str += "  vector<int> results\n";
      str += "  for 0 < i <= pairs.length\n";
      str += "    result.push_back(pairs[i].get<1>())\n";
      str += "  return result\n\n";

      str =  "decrypt(ciphertext, key)\n";
      str += "  numkey = numbersFromKey(key)\n";
      str += "  vector<string> matrix\n";
      str += "  columnSize = ciphertext.length / numkey.length\n";
      str += "  for 0 <= i < numkey.length\n";
      str += "    j = numkey[i]]\n";
      str += "    if(j < ciphertext.length % numkey.length)\n";
      str += "      matrix[j] = ciphertext[0...columnSize]\n";
      str += "      ciphertext = ciphertext[columnSize...]\n";
      str += "    else\n";
      str += "      matrix[j] = ciphertext[0...columnSize + 1]\n";
      str += "      ciphertext = ciphertext[columnSize + 1...]\n";
      str += "  result = \"\"\n";
      str += "  for 0 <= i < ciphertext.length\n";
      str += "    result += matrix[i % key.length][i / key.length]\n";
      str += "  return result\n\n";

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
      std::vector<int> numkey = numbersFromKey(password);
      int numkeyLength = numkey.size();
      std::vector<std::string> matrix;
      int columnSize = plainText.length() / numkeyLength;

      for (int i = 0; i < numkeyLength; i++)
      {
         int j = numkey[i];
         if (j < plainText.length() % numkeyLength)
         {
            matrix[j] = plainText.substr(0,columnSize);
            plainText = plainText.substr(columnSize);
         }
         else
         {
            matrix[j] = plainText.substr(0, ++columnSize);
            plainText = plainText.substr(++columnSize);
         }
      }
      
      std::string result = "";
      int plainLength = plainText.length();
      for (int i = 0; i < plainLength; i++)
      {
         result += matrix[i % password.length()][i / password.length()];
      }
      return result;
   }
};

#endif // CIPHER06_H
