#include <iostream>
#include <string>
#include <sstream>

using namespace std;

// Accepts two strings and returns a query string
string generateQuery(string name, string password)
{
    ostringstream builder;
    builder << "SELECT username FROM authentication" << endl
        << "WHERE username = '" << name << "' "
        << "AND password = '" << password << "'";
    return builder.str();
}

int main()
{
    string username;
    string password;

    cout << "Please enter your username: ";
    cin >> username;

    cout << "\nPlease enter your password: ";
    cin >> password;

    // testing input
    cout << "\n" << generateQuery(username, password) << "\n";
    return 0;
}
