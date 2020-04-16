#include "../Globals/Globals.h"

#define push_hold_voltage 2000
#define push_enc_highest 7000
#define push_enc_lay_tower 2500
#define push_enc_unlock_support_board    1200
#define push_enc_support_delta    1000

extern int push_dir;

#define DIR_PUSH_NONE 0
#define DIR_key_push_out 1
#define DIR_key_push_in -1

void push_set_speed(int v);
void push_set_voltage(int mV);
void handle_push(int push_out, int push_in, int slow_mode);
void push_straight();
void push_reseat();

int get_push_enc();
void push_enc_reset();
void push_goto_highest_according_to_enc();

void push_unlock_thread_start();