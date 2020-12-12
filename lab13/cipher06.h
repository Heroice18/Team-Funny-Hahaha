/********************************************************************
* Header:
*    Implement your cipher here. You can view 'example.h' to see the
*    completed Caesar Cipher example.
********************************************************************/
#ifndef CIPHER06_H
#define CIPHER06_H

#include <algorithm>

/********************************************************************
 * CLASS
 *******************************************************************/
class Cipher06 : public Cipher
{
public:
   virtual std::string getPseudoAuth()  { return "Thomas Peck"; }
   virtual std::string getCipherName()  { return "Columnar Transposition"; }
   virtual std::string getEncryptAuth() { return "Caleb Baird"; }
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
      str += "    result += matrix[numkey[i]]\n";
      str += "  return result\n\n";

      str +=  "numbersFromKey(key)\n";
      str += "  vector<pair<char, int>> pairs\n";
      str += "  for 0 <= i < key.length\n";
      str += "    pairs[i] = pair(key[i], i)\n";
      str += "  stable_sort(pairs.begin, pairs.end, [](a,b){return a.get<0>() < b.get<0>();})\n";
      str += "  vector<int> results\n";
      str += "  for 0 < i <= pairs.length\n";
      str += "    result.push_back(pairs[i].get<1>())\n";
      str += "  return result\n\n";

      str +=  "decrypt(ciphertext, key)\n";
      str += "  numkey = numbersFromKey(key)\n";
      str += "  vector<string> matrix\n";
      str += "  for 0 <= i < key.length\n";
      str += "    matrix[i] = \"\"\n";
      str += "  columnSize = ciphertext.length / numkey.length\n";
      str += "  for 0 <= i < numkey.length\n";
      str += "    j = numkey[i]]\n";
      str += "    if(j < ciphertext.length % numkey.length)\n";
      str += "      matrix[j] = ciphertext[0...columnSize + 1]\n";
      str += "      ciphertext = ciphertext[columnSize + 1...]\n";
      str += "    else\n";
      str += "      matrix[j] = ciphertext[0...columnSize]\n";
      str += "      ciphertext = ciphertext[columnSize...]\n";
      str += "  result = \"\"\n";
      str += "  for 0 <= i < ciphertext.length\n";
      str += "    result += matrix[i % key.length][i / key.length]\n";
      str += "  return result\n\n";

      return str;
   }

   /**********************************************************
    * charIndexSorter :: Simple sorting predicate to arrange
    * the charIndexPairs alphabetically based on the char value.
    **********************************************************/
   static bool charIndexSorter(std::pair<char, int> lhs,
                        std::pair<char, int> rhs)
   {
      return std::get<0>(lhs) < std::get<0>(rhs);
   }

   /**********************************************************
    * numbersFromKey :: Takes a key string and returns a vector
    * of numbers, where each number replaces a letter with its
    * alphabetical order number based on the other letters.
    **********************************************************/
   std::vector<int> numbersFromKey(const std::string & key)
   {
      std::vector<int> results;

      int keySize = key.size();

      // Break the key into a vector of the chars paired with the index.
      std::vector<std::pair<char, int> > charIndexPairs;
      for (int i = 0; i < keySize; ++i)
         charIndexPairs.push_back(std::pair<char, int>(key[i], i));

      // Sort the charIndexPairs by the chars
      std::stable_sort(charIndexPairs.begin(), charIndexPairs.end(),
                       charIndexSorter);

      for (int i = 0; i < keySize; ++i)
         results.push_back(std::get<1>(charIndexPairs[i]));

      return results;
   }

   /**********************************************************
    * ENCRYPT :: Construct a matrix as many columns as there
    * are characters in password. Populate columns with the
    * characters of plainText. Rearrange the columns of the
    * matrix to match the alphabetical order of the password.
    * concatenate columns of matrix to generate ciphertext.
    **********************************************************/
   virtual std::string encrypt(const std::string & plainText,
                               const std::string & password)
   {
      std::vector<std::string> matrix;
      int passwordSize = password.size();

      // Each empty string in this vector is a column of the matrix
      for (int i = 0; i < passwordSize; ++i)
         matrix.push_back("");

      // Add plain text to the matrix by appending to the columns
      for (int i = 0; i < plainText.size(); ++i)
         matrix[i % passwordSize] += plainText[i];

      // get the keyNumbers to know how to rearrange the columns
      std::vector<int> keyNumbers = numbersFromKey(password);

      // Concatenate the rearranged columns into one cipherText string.
      std::string cipherText = "";
      for (int i = 0; i < passwordSize; ++i)
         cipherText += matrix[keyNumbers[i]];

      return cipherText;
   }

   /**********************************************************
    * DECRYPT
    * TODO: ADD description
    **********************************************************/
   virtual std::string decrypt(const std::string & cipherText,
                               const std::string & password)
   {

      std::string text = cipherText;
      std::vector<int> numkey = numbersFromKey(password);
      std::vector<std::string> matrix;

      int numColumns = numkey.size();
      int columnSize = text.length() / numColumns + 1;
      int numLargeColumns = text.length() % numColumns;

      matrix.resize(numColumns, "");

      int cipherTextLength = text.length();
      for (int i = 0; i < numColumns; ++i)
      {
         int j = numkey[i];
         if (j < cipherTextLength % numColumns)
         {
            matrix[j] = text.substr(0, columnSize);
            text = text.substr(columnSize);
         }
         else
         {
            matrix[j] = text.substr(0, columnSize - 1);
            text = text.substr(columnSize - 1);
         }
      }
      std::string plainText = "";
      for (int i = 0; i < cipherTextLength; ++i)
      {
         plainText += matrix[i % numColumns][i / numColumns];
      }

      return plainText;
   }
};

#endif // CIPHER06_H
