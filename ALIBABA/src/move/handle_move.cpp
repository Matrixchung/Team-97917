#include "move.h"

#define JOYSTICK_STABLE_BLIND_AREA 20
#define N_JOYSTICK_VALUE 2

int joystick_stable_small_value_process(int index, int value_new) {
  static vex::timer t[N_JOYSTICK_VALUE];
  static int value_last[N_JOYSTICK_VALUE] = {0, 0};

  int ret;

  if (abs(value_new) > JOYSTICK_STABLE_BLIND_AREA) { // beyond blind area
    t[index].clear();
    ret = value_new;
  } else { // in blind area
    int sudden = abs(value_last[index] - value_new);
    if (sudden > 5) { // sudden change
      t[index].clear();
      ret = value_new;
    } else {
      if (t[index].time() > 500) // stable in blind area for over 500ms
        ret = 0;
      else
        ret = value_new;
    }
  }
  // cout << index << ":  " << value_last[index] << "  " << value_new << "  "
  //      << ret << endl;
  value_last[index] = value_new;
  return ret;
}


//////////////////////////////////////////////////////////////////需要调试
void move_ctrl(int forward, int turn) {
  int pf;
  int pt;

  zero_blind(forward, 5);
  zero_blind(turn, 5);

  pf = forward /100.0*12800;
  pt = turn /100.0*12800;
  move_set_voltage(pf, pt);
}
//////////////////////////////////////////////////////////////////////////
void handle_move(int chx_forward, int chx_turn, int slow_mode) {

  if (abs(chx_forward) > 20 || abs(chx_turn) > 20)
    b_all_motor_float = false;

  chx_forward = joystick_stable_small_value_process(0, chx_forward);
  chx_turn = joystick_stable_small_value_process(1, chx_turn);

  if (slow_mode) {
    int s_forward = chx_forward/100.0*12800 * 0.3;
    int s_turn = chx_turn/100.0*12800 * 0.3;
    max_limit(s_forward, 20);
    max_limit(s_turn, 20);
    move_ctrl(s_forward, s_turn);
  } else
    move_ctrl(chx_forward, chx_turn);
}
