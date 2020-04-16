#include "../Globals/Globals.h"
#include "../move/move.h"

float GyroGetAngle();
float get_gyro() {
  wait(1);
  // return GyroGetAngle();
  return gyro_z.value(rotationUnits::deg);
}

void resetTheGyro(bool key) {
  if (key) {
    gyro_z.resetAngle();
  }
}

int get_gyro_err(int aim_final_x, int val_now) {
  int err = aim_final_x - val_now;
  if (err > 180)
    err = err - 360;
  if (err < -180)
    err = err + 360;
  return err;
}
/////////////////////////////////////////////////////////////////////////
void turn_pid_absolute(int aim_final, int time_out, int forward,
                       int max_speed) {
  float kp = 0.5;
  float output, err;

  vex::timer t0;

  while (t0.time() < time_out) {
    err = get_gyro_err(aim_final, get_gyro());
    output = kp * err;
    if (output > max_speed)
      output = max_speed;
    if (output < -max_speed)
      output = -max_speed;

    move(forward, output);
    wait(10);

    // err break
    if (abs(err) <= 2)
      break;
  }
  move_stop();
}
/////////////////////////////////////////////////////////////////////////
void turn_pid_relative(int aim_relative, int time_out, int forward,
                       int max_speed) {
  int begin_val = get_gyro();
  int aim_final = begin_val + aim_relative;
  if (aim_final > 360)
    aim_final -= 360;
  if (aim_final < -360)
    aim_final += 360;
  turn_pid_absolute(aim_final, time_out, forward, max_speed);
}