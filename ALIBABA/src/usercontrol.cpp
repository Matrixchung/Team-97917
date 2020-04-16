#include "_includes.h"

bool flag_push_auto_reset = true;

void push_usercontrol_auto_reset() {
  if (get_push_enc() == 0) {
    push_dir = DIR_PUSH_NONE;
    flag_push_auto_reset = false;
    return;
  }

  flag_push_auto_reset = true;
  push_set_voltage(-12800);
  while (get_push_enc() > 500)
    ;

  push_set_voltage(-4000);
  while (get_push_enc() > 300)
    ;
  push_set_voltage(-1500);
  flag_push_auto_reset = false;
  push_dir = DIR_key_push_in;
}

void usercontrol(void) {

  thread th_push_auto_reset(push_usercontrol_auto_reset);

  while (1) {
    wait(5);
    if (!auto_testing) {

      // cout << "b_all_motor_float:" << b_all_motor_float << endl;
      // cout << "b_all_motor_already_brake:" << b_all_motor_already_brake << endl;

      if (b_all_motor_float == false) {

        // cout << "try to brakr..." << endl;
        all_motor_brake();
        // b_all_motor_already_brake = true;
      }
      // wait(400);
      // Print(0, 220, "xxxx%d ", b_all_motor_float?1:0);

      if (Controller.ButtonRight.pressing()) {
        reset_all_encoders();
        b_all_motor_float = false;
      }

      bSlowMode = Controller.ButtonA.pressing();

      handle_move(Controller.Axis3.position(), Controller.Axis4.position(),
                  bSlowMode);
      handle_intake(Controller.ButtonR1.pressing(),
                    Controller.ButtonR2.pressing(), bSlowMode);
      handle_swing(Controller.Axis2.position(), bSlowMode);

      if (th_push_auto_reset.joinable()) // running
        if (Controller.ButtonL2.pressing() || Controller.ButtonL1.pressing()) {
          th_push_auto_reset.interrupt();
          flag_push_auto_reset = false;
        }

      ///////////////////////////////////////////////
      switch (ROBOT) {
      case R_Normal:
      case R_74000M:
      case R_74000P:
      case R_74000F:
      case R_74000V:
        if (!flag_push_auto_reset)
          handle_push(Controller.ButtonL2.pressing(),
                      Controller.ButtonL1.pressing(), bSlowMode);
        break;

      case R_77921F:
        if (!flag_push_auto_reset)
          handle_push(Controller.ButtonL1.pressing(),
                      Controller.ButtonL2.pressing(), bSlowMode);
        break;
      default:
        break;
      }
    } else
      wait(50);
  }
}