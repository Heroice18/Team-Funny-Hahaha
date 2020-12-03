#include "control.h"

// was just copy pasted in. Needs to be moved!
bool securityConditionRead(Control assetControl, Control subjectControl)
{
   return subjectControl >= assetControl;
}

// was just copy pasted in. Needs to be moved!
bool securityConditionWrite(Control assetControl, Control subjectControl)
{
   return subjectControl <= assetControl; // opposite of the Read!
}
