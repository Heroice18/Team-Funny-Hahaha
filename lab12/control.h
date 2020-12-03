/***********************************************************************
 * COMPONENT:
 *    CONTROL
 * Author:
 *    Br. Helfrich, <your name here if you made a change>
 * Summary:
 *    This class stores the notion of Bell-LaPadula
 ************************************************************************/

#pragma once

// you may need to put something here...
enum CONTROL
{
    UNCLASSIFIED, PUBLIC, CONFIDENTIAL, SECRET, TOP_SECRET
};

// was just copy pasted in. Needs to be moved!
bool securityConditionRead(Control assetControl, /* asset control */ Control subjectControl /* request control*/)
{
return subjectControl >= assetControl;
}

// was just copy pasted in. Needs to be moved!
bool securityConditionWrite(Control assetControl, /* asset control */ Control subjectControl /* request control*/)
{
return subjectControl <= assetControl; // opposite of the Read!
}

