#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <algorithm>
#include <stdlib.h>
#include <unistd.h>
#define PATH_MAX        4096    /* # chars in a path name including nul */

// Split a delimited string into a vector of strings;
// based on code from: https://stackoverflow.com/a/236803
std::vector<std::string> split(std::string input, char delimiter)
{
    std::istringstream data(input);
    std::string temp;
    std::vector<std::string> output;

    while(std::getline(data, temp, delimiter))
    {
        output.push_back(temp);
    }
    return output;
}

// Join a vector of strings into a single string. Inverse of split.
std::string join(std::vector<std::string> words, char delimiter)
{
    std::string out;
    bool first = true;
    for(auto it = words.begin(); it != words.end(); it++)
    {
        if(!first)
        {
            out += delimiter;
        }
        else
        {
            first = false;
        }
        out += *it;
    }
    return out;
}

// Get the current working directory (inspired by stackOverflow)
// https://stackoverflow.com/questions/298510/how-to-get-the-current-directory-in-a-c-program
std::string getCurrentWorkingDirectory() {

   std::string result = "";
   char cwd[PATH_MAX];

   if (getcwd(cwd, sizeof(cwd)) != NULL) {
      result = cwd;
   } else {
      std::cerr << "getcwd() failed";
   }

   return result;
}

// The canonicalization function.
// Will convert any file path into a simple, absolute path.
std::string cannon(std::string inputPath)
{
    std::vector<std::string> inputDirs = split(inputPath, '/');
    std::vector<std::string> outputDirs;

    auto it = inputDirs.begin();

    if(*it == "") //absolute path
    {
        it++; //skip inital empty string
    }
    else if(*it == "~") //path from HOME
    {
       std::string homeDir = getenv("HOME");

        it++;
        //populate outputDirs from the home path
        outputDirs = split(homeDir, '/');
        //remove empty strings from the path
        outputDirs.erase(remove(outputDirs.begin(), outputDirs.end(), ""), outputDirs.end());
    }
    else //relative path
    {
       std::string workingDir = getCurrentWorkingDirectory();

        outputDirs = split(workingDir, '/');
        outputDirs.erase(remove(outputDirs.begin(), outputDirs.end(), ""), outputDirs.end());
    }

    for(; it != inputDirs.end(); it++)
    {
        if(*it == "..")
        {
            if(!outputDirs.empty())
            {
                outputDirs.pop_back();
            }
        }
        else if(*it != "." && *it != "")
        {
            outputDirs.push_back(*it);
        }
    }
    return '/' + join(outputDirs, '/');
}

// returns whether the two paths are the same
bool isHomograph(std::string path1, std::string path2)
{
    if (cannon(path1) != cannon(path2)) {
        return true;
    }
    else
        return false;
}


int main(int argc, char * argv[])
{
    std::string path1;
    std::string path2;

    std::cout << "Specify the first filename: ";
    std::cin >> path1;

    std::cout << "Specify the second filename: ";
    std::cin >> path2;

    if (isHomograph(path1, path2) == true)
    {
        std::cout << '\n' << "The paths are NOT homographs" << '\n';
    }
    else
    {
        std::cout << '\n' << "The paths are homographs" << '\n';
    }


}