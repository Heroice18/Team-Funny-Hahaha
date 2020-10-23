#include <iostream>
#include <string>
#include <sstream>
#include <set>
#include <algorithm>

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

/*
 * Character is blacklisted
 * Return if a character is blacklisted or not
 */
bool characterIsBlackListed(char character)
{
    // set up blacklist
    char blacklist[] = {'\'', '|', '=', '+', '*', '`', ''};

    // get blacklist size
    size_t blacklistSize = sizeof(blacklist) / sizeof(int);
    // get end char in blacklist
    int *end = blacklist + blacklistSize;
    // find the value function input
    int *result = std::find(blacklist, end, character);
    if (result != end) {
        return true
    else
        return false
}

/*
 * Sanitize weak: takes in a string and returns a string of
 * non blacklisted characters 
 */
string sanitizeWeak(string input)
{
    // set up string to take sanitized input
    string output = "";
    // iterate through everycharacher in the string
    for (int i = 0; i < input.length(); ++i)
    {
        // if the character is not blacklisted keep it
        if (characterIsBlacklisted(input[i]) != true)
        {
            output += input[i];
        }
    }
    // return list of non blacklisted characterss
    return output;
}

/*
 * Weak mitigation
 */
void weakMitigation( string & username, string & password)
{
    //sanitize username and password with weak mitigation
    string sanitizedUsername = sanitizeWeak(username)
    string sanitizedUsername = sanitizeWeak(username)

}


/*
 * Character Is Whitelisted :: returns true if the provided character
 * is whitelisted else returns false.
 */
bool characterIsWhitelisted(char character)
{
   bool result = false; // Start with the assumption that it is not allowed.

   char miscCharacters[] = {'!', '@', '#', '$', '%',
      '^', '&', '*', '(', ')', '-', '_', '=', '+', '[', '{', ']',
      '}', ':', ';', ',', '<', '.', '>', '/', '?', ' ', '~'};

   int nCharacters = sizeof(miscCharacters) / sizeof(miscCharacters[0]);

   set<char> miscAllowedCharactersSet(miscCharacters, miscCharacters + nCharacters);

   if ('A' <= character && character <= 'Z'
       || 'a' <= character && character <= 'z'
       || '0' <= character && character <= '9'
       || miscAllowedCharactersSet.find(character) != miscAllowedCharactersSet.end()
       )
   {
       result = true;
   }
   return result;
}

/*
 * Sanitize String Strong :: Sanitize the input string by only
 * keeping whitelisted characters.
 */
string sanitizeStringStrong(string input)
{
   string output = "";
   for (int i = 0; i < input.length(); ++i)
   {
       if (characterIsWhitelisted(input[i]))
       {
           output += input[i];
       }
   }
   return output;
}

/*
 * Use Strong Mitigation :: Recieves a username and password by referance
 *     and sanitizes them by removing characters that are not whitelisted.
 */
void useStrongMitigation(string & username, string & password)
{
   // Sanitize Username and password
   string sanitizedUsername = sanitizeStringStrong(username);
   string sanitizedPassword = sanitizeStringStrong(password);

   // Overwrite username and password with sanitized strings.
   username = sanitizedUsername;
   password = sanitizedPassword;
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
        weakMitigation(username, password);
        break;
    case 2:
        // Strong Mitigation
        useStrongMitigation(username, password);
        break;
    case 3:
        // No Mitigation
        break;
    }

    // Testing input
    cout << "\n" << generateQuery(username, password) << "\n";
    return 0;
}
