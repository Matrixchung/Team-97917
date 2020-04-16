#include "../Globals/Globals.h"
#include "../_includes.h"

#define MOVE_FULL_VOLTAGE 12800

void auto_role_one_1() {
  
  // timer t;
  // float agl;
  // int dist;
  // int gyro_begin_zero_value = get_gyro();

  // reset_all_encoders();

  // // goto test_begin;

  // // robot functional units initialize
  // if (1) {
  //   swing_set_voltage(-2000); // swing
  //   push_set_voltage(-1500);
  // }

  // // unlock
  // if (1) {
  //   unlock_robot();
  //   cout << "unlock time:" << t.time(timeUnits::msec) << endl;
  // }

  // // forward to intake snake 2/
  // if (1) {
  //   swing_set_voltage(-1500);
  //   intake_full_power_in();
  //   move_enc_reset();

  //   move(40, 0); ////////////////////////////////////////////old
  //   while (get_move_enc() < 3100)
  //     ;
  //   move_stop();
  // }

  // if (1) {
  //   move(-90, auto_info.side * 60);
  //   wait(550);
  //   move_enc_reset();
  //   move(-100, 0);
  //   while (get_move_enc() < -3000)
  //     ;
  //   turn_pid_absolute(0, 1000);
  // }

  // if (1) {
  //   swing_set_voltage(-1500);
  //   intake_for_time_thread(12800, 3800);
  //   move_enc_reset();

  //   move(30, 0); ////////////////////////////////////////////old
  //   while (get_move_enc() < 3100)
  //     ;
  //   move_stop();
  // }

  // if (1) {

  //   move(-100, 0);
  //   wait(300);
  //   turn_pid_absolute(auto_info.side * -127, 2000);
  // }

  // if (1) {
  //   move(100, 0);
  //   push_set_voltage(6000);
  //   while (get_move_enc() < 2400)
  //     ;
  //   // get stuck to the zone
  //   move_set_voltage(1500, 0);
  //   push_set_voltage(6000);
  //   wait(250);
  //   intake_set_voltage(-1500);
  //   // move_set_voltage(-1500, 0);
  //   // wait(100);
  // }

  // if (1) {
  //   // lay the cube into the zone
  //   push_straight_auto();
  //   move(-100, 0);
  //   wait(400);
  // }

  // cout << "auto time: " << t.time(timeUnits::msec) << endl;

  // // print time
  // cout << t.time(timeUnits::msec) << endl;
}
