#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <algorithm>
#include <stdlib.h>

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

std::string cannon(std::string inputPath)
{
    std::string homeDir = getenv("HOME");
    std::string workingDir = "/Users/test/current/working/dir";

    auto dirs = split(inputPath, '/');
    std::vector<std::string> final;

    auto it = dirs.begin();

    if(*it == "")
    {
        it++;
    }
    else if(*it == "~")
    {
        it++;
        final = split(homeDir, '/');
    }
    else{
        final = split(workingDir, '/');
    }

    for(; it != dirs.end(); it++){
        if(*it == ".."){
            if(!final.empty()){
                final.pop_back();
            }
        }
        else if(*it != "."){
            final.push_back(*it);
        }
    }
    return '/' + join(final, '/');
}

int main(int argc, char * argv[]) {
    std::string path;
    std::cout << "Path: ";
    std::cin >> path;
    std::cout << '\n' << "Cannon: " << cannon(path) << '\n';
}
