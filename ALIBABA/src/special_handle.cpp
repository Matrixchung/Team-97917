#include "_includes.h"

void special_key_handle() {
  if (Controller.ButtonLeft.pressing()) {
    // before
    stop_all_motors();

    if (b_all_motor_float == false) {
      all_motors_float();
      b_all_motor_float = true;
      b_all_motor_already_brake = false;
    }

    intake_dir = 0;
    push_dir = 0;

    while (Controller.ButtonLeft.pressing()) {
      // key up
      resetTheGyro(Controller.ButtonUp.pressing());

      // key right
      if (Controller.ButtonRight.pressing()) {
        auto_testing = true;
        while (Controller.ButtonRight.pressing() ||
               Controller.ButtonLeft.pressing()) {
        } // wait for release
        vex::thread th_auto_test(autonomous);

        // th_auto_test.join();//wait for autonomous completely finished
        while (th_auto_test.joinable()) {
          if (Controller.ButtonLeft.pressing()) {
            th_auto_test.interrupt(); // stop
            stop_all_motors();
          }
          wait(50);
        }
        stop_all_motors();
        auto_testing = false;
      } // key right
    }   // while(key left)
    /////////////////////////////
    // after
    ///
  } // key left
}