#include "../Globals/Globals.h"
#include "../_includes.h"

void auto_role_two_1() {
  // timer t;
  // float agl;
  // int dist;
  // int gyro_begin_zero_value = get_gyro();

  reset_all_encoders();
  // goto test_begin;

  // robot functional units initialize
  if (1) {
    swing_set_voltage(-2000); // swing
    push_set_voltage(-1500);
  }

  // unlock
  if (1) {
    unlock_robot();
    //cout << "unlock time:" << t.time(timeUnits::msec) << endl;
  }

  // if (1) {
  //   intake_for_time_thread(12800, 10000);
  //   move_set_voltage(8000, 0);
  //   // brake the snake 4
  //   while (get_move_enc() < 800)
  //     ;
  //   move_set_voltage(11500, 0);
  //   while (get_move_enc() < 1700)
  //     ;
  //   wait(200);

  //   // take the cube from snake 4
  //   move_set_voltage(-12800, 0);
  //   while (get_move_enc() > 1000)
  //     ;
  //   move_set_voltage(12800, 0);
  //   while (get_move_enc() < 1800)
  //     ;
  //   move_set_voltage(4500, 0);
  //   while (get_move_enc() < 3200)
  //     ;
  // }

  // // get the lonely one next to the tower
  // if (1) {
  //   move(-80, 0);
  //   while (get_move_enc() > 2600)
  //     ;
  //   // turn to the cube
  //   turn_pid_absolute(27 * auto_info.side, 1000, 0, 50);
  //   // take the cube
  //   move_enc_reset();
  //   move_set_voltage(6000, 0);
  //   intake_set_voltage(12800);
  //   wait(1150);
  //   intake_set_voltage(12800);
  //   wait(100);
  // }

  // if (1) {
  //   // prepare for turn(go back)
  //   move_set_voltage(-8960, 0);
  //   while (get_move_enc() > 100)
  //     ;

  //   // turn to the zone
  //   turn_pid_absolute(auto_info.side * 110, 2000, 0, 50);

  //   // move forward to get close to the cube near zone
  //   move_enc_reset();
  //   move_set_voltage(12800, 0);
  //   while (get_move_enc() < 1300)
  //     ;

  //   // take the cube near the zone
  //   move_set_voltage(4000, 0);
  //   intake_set_speed(100);
  //   while (get_move_enc() < 1700)
  //     ;

  //   // turn to the zone correctly and get close to the zone
  //   turn_pid_relative(auto_info.side * 4, 2000);
  //   move(50, 0);
  //   wait(700);
  //   // get stuck to the zone
  //   move_set_voltage(-1500, 0);
  //   wait(100);
  //   move_set_voltage(1500, 0);
  //   intake_set_voltage(-1500);
  //   wait(300);
  // }

  // if (1) {
  //   // lay the cube into the zone
  //   push_straight_auto();
  //   move(-100, 0);
  //   wait(400);
  // }

  // // print the time
  // cout << t.time() << endl;
}