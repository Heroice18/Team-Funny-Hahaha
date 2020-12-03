/***********************************************************************
 * COMPONENT:
 *    CONTROL
 * Author:
 *    Br. Helfrich, Caleb Baird, Thomas Peck, Jonathan Hald, and Ethan
 *    Nelson.
 * Summary:
 *    This class stores the notion of Bell-LaPadula
 ************************************************************************/

#pragma once


enum Control
{
   PUBLIC, CONFIDENTIAL, PRIVILEGED, SECRET
};


bool securityConditionRead(Control assetControl, Control subjectControl);

bool securityConditionWrite(Control assetControl, Control subjectControl);
