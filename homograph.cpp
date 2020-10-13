#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <algorithm>

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
        if(!out.empty())
        {
            out += delimiter;
        }
        out += *it;
    }
    return out;
}

std::string cannon(std::string inputPath, std::string workingDir = "")
{
    auto dirs = split(inputPath, '/');
    std::vector<std::string> final;
    for(auto it = dirs.begin(); it !=dirs.end(); it++){
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
    std::cout << "Cannon: " << cannon(path);
}
