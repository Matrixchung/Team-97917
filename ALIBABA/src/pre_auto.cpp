#include "Globals/Globals.h"

void pre_auton(void) {
  all_motor_brake();

  switch (ROBOT) {
  case R_Normal:
    Controller.Screen.print("R_Normal");
    break;
  case R_74000M:
    Controller.Screen.print("R_74000M");
    break;
  case R_74000V:
    Controller.Screen.print("74000V~~~~~~");
    break;
  case R_74000P:
    Controller.Screen.print("R_74000P");
    break;
  case R_74000F:
    Controller.Screen.print("R_74000F");
    break;
  case R_77921F:
    Controller.Screen.print("R_77921F");
    break;
  default:
    break;
  }
}
