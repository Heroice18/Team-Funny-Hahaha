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
// Displays a menu of attacks the user can select
void displayAttackMenu()
{
    cout << "\nWhat kind of attack would you like to use? \n";
    cout << "------------------------------------------\n";
    cout << "\tUnion Query          -- type 1\n";
    cout << "\tTautology            -- type 2\n";
    cout << "\tComment              -- type 3\n";
    cout << "\tAdditional Statement -- type 4\n";
    cout << "\tNo Attack            -- type 5\n";
    cout << "------------------------------------------\n";
}

// Displays a menu of mitigation the user can select
void displayMitigationMenu()
{
    cout << "\nWhat kind of mitigation would you like to use?\n";
    cout << "----------------------------------------------\n";
    cout << "\tWeak Mitigation      -- type 1\n";
    cout << "\tStrong Mitigation    -- type 2\n";
    cout << "\tNo Mitigation        -- type 3\n";
    cout << "----------------------------------------------\n";
}
int main()
{
    string username;
    string password;
    int attack;
    int mitigation;

    //TO DO: add switch statements to select between four attack and if none, weak, or strong mitigation.

    // User selects what could of attack they want to test
    displayAttackMenu();
    cin >> attack;
    switch (attack)
    {
    case 1:
        // Union Query Attack
        username = "Sarah";
        password = "nothing' UNION SELECT authenticate FROM passwordList";
        break;
    case 2:
        // Tautology Attack
        username = "Tim";
        password = "nothing' OR 'x' = 'x";
        break;
    case 3:
        // Comment Attack
        username = "Root'; --";
        password = "nothing";
        break;
    case 4:
        // Additional Statement Attack
        username = "Root";
        password = "nothing'; INSERT INTO passwordList (name, passwd) VALUES 'Bob', '1234";
        break;
    case 5:
        // No Attack
        cout << "Please enter your username: ";
        cin >> username;
        cout << "Please enter your password: ";
        cin >> password;
        break;
    }

    // User selects what kind of mitigation they want to use
    displayMitigationMenu();
    cin >> mitigation;
    switch (mitigation)
    {
    case 1:
        // Weak Mitigation
        //weakMitigation();
        break;
    case 2:
        // Strong Mitigation
        //strongMitigation();
        break;
    case 3:
        // No Mitigation
        break;
    }

    // Testing input
    cout << "\n" << generateQuery(username, password) << "\n";
    return 0;
}
