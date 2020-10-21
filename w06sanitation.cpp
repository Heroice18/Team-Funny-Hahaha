//This is the start of the file

#include <iostream>

// accepts two strings and returns them as a single string
std::string query(std::string username, std::string password)
{
    std::string userAndPass = username + password;
    return userAndPass;
}

int main()
{
    std::string username;
    std::string password;

    std::cout << "Please enter your username: ";
    std::cin >> username;

    std::cout << "\nPlease enter your password: ";
    std::cin >> password;

    // testing input
    std::cout << "\n" << query(username, password) << "\n";
    return 0;
}
