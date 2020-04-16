#include "../Globals/Globals.h"

void move(int forward, int turn) ;
void move_set_speed(int forward, int turn);
void move_set_voltage(int forward, int turn);

#define   move_stop()   { move(0, 0);wait(10);}

void handle_move(int chx_forward, int chx_turn, int slow_mode);

int get_move_enc(int side = -1);
void move_enc_reset();

void move_motors_float_mode();
void move_motors_brake_mode();