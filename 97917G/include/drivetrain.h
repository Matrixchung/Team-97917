#include "vex.h"

extern bool b_all_motor_float;
void move(int forward, int turn) ;
void move_set_speed(int forward, int turn);
void move_set_voltage(int forward, int turn);
void move_LR_set_voltage(float vl, float vr);
#define   move_stop()   { move(0, 0);wait(10);}

void handle_move(int chx_forward, int chx_turn, int slow_mode);

int get_move_enc(int side = -1);
void move_enc_reset();

void move_motors_float_mode();
void move_motors_brake_mode();
void move_set_voltage(int forward,int turn);
void all_motor_brake();
void all_motors_float();
void stop_all_motors();
void move_enc_reset();
void move_motors_brake_mode();
void move_motors_float_mode();
void move_LR_set_voltage(float vl, float vr);
void allEnableRecording();
void allDisableRecordingOrPlayback();
void allEnablePlayback();
void allSaveRecording();
void allDisablePlayback();
void allLoadRecording();