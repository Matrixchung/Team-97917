#include "../push/push.h"

#define push_unlock_enc 500

void push_unlock_service() {
  push_set_speed(DIR_key_push_out * 80);
  while (get_push_enc() < push_unlock_enc) {
  };
  push_set_speed(DIR_key_push_out * 0);
  wait(1000);
  push_set_speed(DIR_key_push_in * 60);
  while (get_push_enc() > 100) {
  };
  push_set_voltage(DIR_key_push_in * 1300);
}

void push_unlock_thread_start() { vex::thread th(push_unlock_service); }



#define enc_push_begin_slow_down 2000

void push_goto_highest_according_to_enc() {
  static int err;
  static int output;
  static float kp = 7;

  err = push_enc_highest - abs(get_push_enc());

  
  if (err > enc_push_begin_slow_down) {//far from stragigt
    output = err * kp;
    if (output > 12800)
      output = 12800;
    if (output < 2500)
      output = 2500;
    push_set_voltage(output);
  } else {
    if (limit_push_max.pressing())
      push_set_voltage(2000);
    else
      push_set_speed(30);
  }

  if (limit_push_max.pressing()) {
    push_set_voltage(2000);
  }
}