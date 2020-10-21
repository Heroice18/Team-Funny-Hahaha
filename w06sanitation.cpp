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

string weakMitigation()
{
    //TO DO
}

string strongMitigation()
{
    //TO DO
}
int main()
{
    string username;
    string password;

    //TO DO: add switch statements to select between four attack and if none, weak, or strong mitigation.
    cout << "Please enter your username: ";
    cin >> username;

    cout << "Please enter your password: ";
    cin >> password;

    // Testing input
    cout << "\n" << generateQuery(username, password) << "\n";
    return 0;
}
