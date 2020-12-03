#include "control.h"


bool securityConditionRead(Control assetControl, Control subjectControl)
{
   return subjectControl >= assetControl;
}


bool securityConditionWrite(Control assetControl, Control subjectControl)
{
   return subjectControl <= assetControl; 
}
