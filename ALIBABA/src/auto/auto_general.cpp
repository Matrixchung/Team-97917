#include "../_includes.h"

void forward_to_postion(int speed, int aim_position_enc, int after_speed) {
  move(speed, 0);
  if (sgn(speed) == -1) {
    while (get_move_enc() > aim_position_enc) {
    };

  } else {
    while (get_move_enc() < aim_position_enc) {
    };
  }
  move(after_speed, 0);
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void push_up_and_down_and_push_enc_reset_thread() {
  push_set_voltage(12800); // push hold out
  while (get_push_enc() < push_enc_unlock_support_board)
    ;

  push_set_voltage(-12800); // push hold out
  while (get_push_enc() > push_enc_support_delta)
    ;
  push_enc_reset();
  push_set_voltage(-1500);
}

void push_support_board_reset_thread_start() {
  vex::thread th(push_up_and_down_and_push_enc_reset_thread);
}
//////////////////
void swing_reset_thread() {
  swing_set_voltage(-12800); // push hold out
  while (get_swing_enc() > 100)
    ;
  swing_set_voltage(-1500);
}

void swing_reset_thread_start() { vex::thread th(swing_reset_thread); }
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void unlock_robot() {
  reset_all_encoders();
  swing_set_voltage(-2000); // swing

  forward_enc(450, 400, 0, 60); // push preload forward and unlock anti-down
  forward_enc(300, 200);        // push preload forward and unlock anti-down

  swing_set_voltage(128000);    // unlock tray
  push_support_board_reset_thread_start();

  move_set_voltage(-3500, 0); // stick to back wall

  while (get_swing_enc() < 1000)
    ;
  swing_set_voltage(0);
  intake_unlock_service(); // block function
  swing_reset_thread_start();
  wait(300);

  // intake_unlock_thread_start();
  wait(100);               // wait for intake roller set
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void push_straight_auto() {
  push_set_voltage(12800);
  while (get_push_enc() < 5000)
    ;

  intake_set_voltage(-1000);

  while (1) {
    int err;

    err = push_enc_highest - abs(get_push_enc());

    if (err > 1350) {
      push_set_voltage(7000);
      intake_set_voltage(2000);
    } else if (err > 600)
      push_set_voltage(5000);
    else if (err > 300) {
      push_set_speed(5);
      move_set_voltage(3000, 0);
    } else // almost straight
      push_set_speed(5);

    // Stop Condition
    if (abs(mtr_push.velocity(velocityUnits::rpm)) <= 3 || limit_push_max) {
      cout << "push stuck..." << endl;
      push_set_voltage(3000);
      break;
    }

    if (get_push_enc() > push_enc_highest - 200) {
      cout << "push beyond limit..." << endl;
      push_set_voltage(2000);
      wait(400);
      break;
    }

    wait(5);
  }
}

////////////////////////////////////////////////////////////////////////////////
void lay_cubes_into_zone(bool x) {
  push_straight_auto();
  wait(200);
  move(-70, 0);
}
