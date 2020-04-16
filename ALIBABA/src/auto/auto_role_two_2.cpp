#include "../_includes.h"

// void push_position_reset() {
//   if (!limit_push_min) {
//     push_set_speed(-50);
//   }
//   else push_set_speed(0);
// }

void auto_role_two_2() {
 // timer t;

  reset_all_encoders();
  // goto test_begin;

  //push_position_reset();
  // unlock
  if (1) {
    unlock_robot();
    //cout << "unlock time:" << t.time(timeUnits::msec) << endl;
  }

  // if (1) {//get close to shake 1
  //   move_set_speed(100, 0);
  //   while (get_move_enc() < 1300)
  //     ;
  //   turn_pid_absolute(auto_info.side * -30, 1000);
  // }


  // if (1) {//break it and intake it
  //   intake_for_time_thread(12800, 3200);//intake for a long time
  //   move(90, 0);
  //   wait(800);
  //   move(50, 0);
  //   wait(550);
  // }

  // if (1) {//return a little distance and wait for another intake   
  //   move_set_speed(-50, 0);
  //   wait(500);
  //   move(0, 0);
  //   wait(200);
  // }

  // if (1) {//move forward
  //   move_set_speed(70, 0);
  //   wait(550);
  // }

  // if (1) {//go back and prepare for turn
  //   move_enc_reset();
  //   move_set_speed(-100, 0);
  //   while (get_move_enc() > -340)
  //     ;
  // }

  // if (1) {//turn back
  //   turn_pid_relative(-178, 1000);
  // }

  // if (1) {
  //   intake_set_voltage(12800);
  //   move_set_voltage(4000, 0);
  //   wait(1700);
  //   turn_pid_absolute(0, 1000);
  // }

  

  // if (1) {
  //   turn_pid_absolute(auto_info.side*29, 1000);
  // }

  // if(1){
  //   move(30, 0);
  //   intake_set_voltage(12800);
  //   while(get_move_enc()<1000);
  // }

  // if (1) {
  // }
  // cout << t.time() << endl;
}
