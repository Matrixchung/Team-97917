
#include "swing.h"

/////////////////////////////////////////
void handle_swing(int chx, int slow_mode) {
  if (abs(chx) > 30)
    b_all_motor_float = false;

  static int dir = 0;
  if (abs(chx) <= 2)
    chx = 0;

  if (chx != 0) {
    dir = sgn(chx);
    if (slow_mode)
      swing_set_voltage(chx / 100.0 * 12000);
    else
      swing_set_voltage(chx / 70.0 * 12000);
  } else
    swing_set_voltage(dir * swing_hold_voltage);
}
