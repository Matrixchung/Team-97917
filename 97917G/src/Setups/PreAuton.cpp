#include "vex.h"
using namespace vex;
extern controller Controller;
void teamcode_display()
{
  switch(Robot)
  {
    case R_97917G:
     Controller.Screen.print("97917G");
     break;
    case R_97917A:
     Controller.Screen.print("97917A");
     break;
    default:
     break;
  }
}