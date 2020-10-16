#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <algorithm>
#include <stdlib.h>
#include <unistd.h>

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

// The canonicalization function.
// Will convert any file path into a simple, absolute path.
std::string cannon(std::string inputPath)
{
    std::string homeDir = getenv("HOME");

    // Get the current working directory (inspired by stackOverflow)
    // https://stackoverflow.com/questions/298510/how-to-get-the-current-directory-in-a-c-program
    std::string workingDir = "";
    char cwd[PATH_MAX];
    if (getcwd(cwd, sizeof(cwd)) != NULL) {
       workingDir = cwd;
    } else {
       std::cerr << "getcwd() failed";
       return "";
    }

    std::vector<std::string> inputDirs = split(inputPath, '/');
    std::vector<std::string> outputDirs;

    auto it = inputDirs.begin();

    if(*it == "") //absolute path
    {
        it++; //skip inital empty string
    }
    else if(*it == "~") //path from HOME
    {
        it++;
        //populate outputDirs from the home path
        outputDirs = split(homeDir, '/');
        //remove empty strings from the path
        remove_if(outputDirs.begin(), outputDirs.end(), [](std::string s){return s=="";});
    }
    else //relative path
    {
        outputDirs = split(workingDir, '/');
        remove_if(outputDirs.begin(), outputDirs.end(), [](std::string s){return s=="";});
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

std::string filenameToCannon(std::string input)
{
    return cannon(input);
}

// returns whether the two paths are the same
std::string homographSet(std::string path1, std::string path2)
{
    std::string homographTrue = "The paths are homographs";
    std::string homographFalse = "The paths are NOT homographs";
    
    if (filenameToCannon(path1) != filenameToCannon(path2)) {
        return homographTrue;
    }
    else
        return homographFalse;
}


int main(int argc, char * argv[])
{
    std::string path1;
    std::string path2;

    std::cout << "Specify the first filename: ";
    std::cin >> path1;

    std::cout << "Specify the second filename: ";
    std::cin >> path2;
    // for debugging purposes, NEEDS TO BE DELETED!
    std::cout << '\n' << "Cannon: " << filenameToCannon(path1) << '\n';
    std::cout << '\n' << "Cannon: " << filenameToCannon(path2) << '\n';
    
    std::cout << '\n' << homographSet(path1, path2) << '\n';
    
}
