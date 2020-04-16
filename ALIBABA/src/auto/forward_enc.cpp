#include "../Globals/Globals.h"
#include "../move/move.h"


void forward_enc(int aim_final, int time_out, int turn ,int max_speed) {
  float kp = 0.5;
  float output, err;

  vex::timer t0;

  while (t0.time() < time_out) {
    err = aim_final - get_move_enc();
    output = kp * err;

    if (output > max_speed)
      output = max_speed;
    if (output < -max_speed)
      output = -max_speed;

    move(output, turn);
    wait(10);

    // err break
    if (abs(err) <= 10)
      break;
  }
  move_stop();
}