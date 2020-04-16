#include "../Globals/Globals.h"

#define swing_hold_voltage 800

void swing_set_voltage(int mV);
int get_swing_enc();
void swing_enc_reset();

void handle_swing(int v, int slow_mode);