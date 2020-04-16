#include "../_includes.h"

void sensor_display() {
  int line_y = 0;

  Print(0, line_y += 20, "gyro deg: %.2f   ", gyro_z.value(rotationUnits::deg));
  // Print(0, line_y += 20, "gyro mv: %.2f   ", gyro_z.value(analogUnits::mV) );

  // Print(0, line_y += 20, "gyro_fa : %.2f   ", GyroGetAbsAngle());
  // Print(0, line_y += 20, "gyro_f  : %.2f   ", GyroGetAngle());

  Print(0, line_y += 20, "push : %d   ", get_push_enc());
  Print(0, line_y += 20, "swing: %d   ", get_swing_enc());
  Print(0, line_y += 20, "intake L: %d    ", get_intake_enc(-1));
  Print(0, line_y += 20, "intake R: %d    ", get_intake_enc(1));
  Print(0, line_y += 20, "move L  : %d   ", get_move_enc(-1));
  Print(0, line_y += 20, "move R  : %d   ", get_move_enc(1));
  Print(0, line_y += 20, "limit push: %d   ", limit_push_max.pressing());

}