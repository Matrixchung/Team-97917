#include "../Globals/Globals.h"
#include "../push/push.h"


bool b_push_goto_lay_tower = false;
int push_dir = DIR_PUSH_NONE;

void push_goto_lay_tower() {
  if (get_push_enc() < push_enc_lay_tower)
    push_set_voltage(DIR_key_push_out * 8000);
  else
    push_set_voltage(100);
}

void handle_push(int key_push_out, int key_push_in, int slow_mode) {

  if(limit_push_min)
  {
    push_enc_reset();
  }

  if (key_push_out && !key_push_in) {
    push_dir = DIR_key_push_out;
    if (limit_push_max.pressing())
      push_set_voltage(2000);
    else {
      if (slow_mode)
        push_set_voltage(3000);
      else
        push_goto_highest_according_to_enc();
    }
  } else if (key_push_in && !key_push_out&&!limit_push_min) {
    push_dir = DIR_key_push_in;
    push_set_voltage(-12000);
  } else {

    b_push_goto_lay_tower = (Controller.Axis2.position() > 40);

    if (!b_push_goto_lay_tower) { // normal
      if (push_dir == DIR_key_push_out )
        push_set_voltage(2000);
      else if (push_dir == DIR_key_push_in ) {

        if (get_push_enc() < 500) // tray almost reset
          push_set_voltage(-1500); //-2000

        else if (get_push_enc() < 3000) // tray almost reset
          push_set_voltage(-2000);      //-2000
        else
          push_set_voltage(0);

      } else
        push_set_voltage(0);
    } // normal
    else {
      push_dir=DIR_PUSH_NONE;
      push_goto_lay_tower();
    } // swing up
  }   // both key released
}