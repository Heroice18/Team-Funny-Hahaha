/***********************************************************************
 * COMPONENT:
 *    MESSAGES
 * Author:
 *    Br. Helfrich, <your name here if you made a change>
 * Summary:
 *    This class stores the notion of a collection of messages
 ************************************************************************/

#include <string>     // for convenience
#include <list>       // to store the messages
#include <iostream>   // standard input and output
#include <fstream>    // the messages are read from a file
#include <cassert>    // because I am paraniod
#include "control.h"  // all the Bell-LaPadula code
#include "message.h"  // all the code about a single message
#include "messages.h" // a collection messages

using namespace std;

/***********************************************
 * MESSAGES :: DISPLAY
 * display the list of messages
 ***********************************************/
void Messages::display() const
{
   for (list <Message> :: const_iterator it = messages.begin();
        it != messages.end();
        ++it)
      it->displayProperties();
}

/***********************************************
 * MESSAGES :: SHOW
 * show a single message
 **********************************************/
void Messages::show(int id, Control subjectControl) const
{
   for (list <Message> :: const_iterator it = messages.begin();
        it != messages.end();
        ++it)
      if (it->getID() == id &&
          securityConditionRead(it->getControl(), subjectControl))
         it->displayText();
}

/***********************************************
 * MESSAGES :: UPDATE
 * update one single message
 ***********************************************/
void Messages::update(int id, const string & text, Control subjectControl)
{
   for (list <Message> :: iterator it = messages.begin();
        it != messages.end();
        ++it)
      if (it->getID() == id &&
          securityConditionWrite(it->getControl(), subjectControl))
         it->updateText(text);
}

/***********************************************
 * MESSAGES :: REMOVE
 * remove a single message
 **********************************************/
void Messages::remove(int id, Control subjectControl)
{
   for (list <Message> :: iterator it = messages.begin();
        it != messages.end();
        ++it)
      if (it->getID() == id && securityConditionWrite(it->getControl(), subjectControl))
         it->clear();
}

/***********************************************
 * MESSAGES :: ADD
 * add a new message
 **********************************************/
void Messages::add(const string & text,
                   const string & author,
                   const string & date,
                   const string & textControl,
                   Control subjectControl)
{
   Message message(text, author, date, textControl);
   if (securityConditionWrite(message.getControl(), subjectControl))
      messages.push_back(message);
}

/***********************************************
 * MESSAGES :: READ MESSAGES
 * read the messages from a file
 ***********************************************/
void Messages::readMessages(const char * fileName)
{
   // open the file
   ifstream fin(fileName);
   if (fin.fail())
   {
      cout << "ERROR! Unable to open file "
           << fileName
           << endl;
      return;
   }

   // continue reading until we fail
   while (!fin.fail() && !fin.eof())
   {
      string author;
      string date;
      string text;
      string textControl;
      getline(fin, textControl, '|');
      getline(fin, author, '|');
      getline(fin, date, '|');
      getline(fin, text);

      if (!fin.fail())
      {
         Message message(text, author, date, textControl);
         messages.push_back(message);
      }
   }

   // close up shop!
   fin.close();
}
