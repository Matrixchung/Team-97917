#include "intake.h"

#define intake_hold_voltage 450

int intake_dir = 0;
int get_push_enc();

void handle_intake(int key_up, int key_dn, int key_slow_mode) {

  if (key_up && !key_dn) {
    intake_dir = 1;
    b_all_motor_float = false;
    

    if (key_slow_mode)
      intake_set_voltage(6000);
    else
      intake_set_voltage(12000);

  } else if (key_dn && !key_up) {
    intake_dir = -1;
    b_all_motor_float = false;

    if (key_slow_mode)
      intake_set_voltage(-4000);
    else
      intake_set_voltage(-8000);
  } else { //

    if (intake_dir == 0)
      intake_set_voltage(0);
    else {
      if (get_push_enc() > 7000)
        intake_set_voltage(-1 * intake_hold_voltage);
      else
        intake_set_voltage(1 * intake_hold_voltage);
    }
  }
}
