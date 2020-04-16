#include "_includes.h"

void autonomous(void) {
  int line = 200;

  vex::timer t_auto;
  Print(0, line, "                              ");

  all_motor_brake();
  // reset_all_encoders();

  if (auto_info.role == ROLE_ONE) {
    if (auto_info.route_number == 1)
      auto_role_one_1();
    if (auto_info.route_number == 2)
      auto_role_one_2();
  }

  if (auto_info.role == ROLE_TWO) {
    if (auto_info.route_number == 1)
      auto_role_two_1();
    if (auto_info.route_number == 2)
      auto_role_two_2();
  }

  Print(0, line, "auto time:%.1fs  ", t_auto.time() / 1000.0);
}