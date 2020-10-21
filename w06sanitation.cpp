#include <iostream>
#include <string>
#include <sstream>

using namespace std;

// Accepts two strings and returns a query string
string generateQuery(string username, string password)
{
    ostringstream builder;
    builder << "SELECT username FROM authentication" << endl
        << "WHERE username = '" << username << "' "
        << "AND password = '" << password << "'";
    return builder.str();
}

int main()
{
    string username;
    string password;

    cout << "Please enter your username: ";
    cin >> username;

    cout << "Please enter your password: ";
    cin >> password;

    // testing input
    cout << "\n" << generateQuery(username, password) << "\n";
    return 0;
}
