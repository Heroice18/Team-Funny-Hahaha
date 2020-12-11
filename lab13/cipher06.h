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
      str += "    result += matrix[i]\n";
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
    * charIndexSorter :: Simple sorting predicate to arrange
    * the charIndexPairs alphabetically based on the char value.
    **********************************************************/
   static bool charIndexSorter(std::pair<char, int> lhs,
                        std::pair<char, int> rhs)
   {
      return std::get<0>(lhs) < std::get<0>(rhs);
   }

   /**********************************************************
    * numIndexSorter :: Simple sorting predicate to arrange the
    * numIndexPairs according to the index value.
    **********************************************************/
   static bool numIndexSorter(std::pair<int, int> lhs,
                    std::pair<int, int> rhs)
   {
      return std::get<1>(lhs) < std::get<1>(rhs);
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

      // Now replace the chars with the number.
      std::vector<std::pair<int, int> > numIndexPairs;
      for (int i = 0; i < keySize; ++i)
      {
         std::pair<int, int> p(i + 1, std::get<1>(charIndexPairs[i]));
         numIndexPairs.push_back(p);
      }

      std::stable_sort(numIndexPairs.begin(), numIndexPairs.end(),
                       numIndexSorter);

      for (int i = 0; i < keySize; ++i)
         results.push_back(std::get<0>(numIndexPairs[i]));

      return results;
   }

   /**********************************************************
    * columnNumSorter :: Simple sorting predicate to arrange
    * the columNumPairs by the num value.
   **********************************************************/
   static bool columnNumSorter(std::pair<std::string, int> lhs,
                                 std::pair<std::string, int> rhs)
   {
      return std::get<1>(lhs) < std::get<1>(rhs);
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

      // pair the columns with the keyNumbers so they can be rearranged
      std::vector<std::pair<std::string, int> > columnNumPairs;
      for (int i = 0; i < passwordSize; ++i)
      {
         std::pair<std::string, int> p(matrix[i], keyNumbers[i]);
         columnNumPairs.push_back(p);
      }

      // Rearrange the columns
      std::stable_sort(columnNumPairs.begin(), columnNumPairs.end(),
                       columnNumSorter);

      // Concatenate the rearranged columns into one cipherText string.
      std::string cipherText = "";
      for (int i = 0; i < passwordSize; ++i)
         cipherText += std::get<0>(columnNumPairs[i]);

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
