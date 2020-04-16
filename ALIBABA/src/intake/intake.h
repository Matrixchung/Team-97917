#include "../Globals/Globals.h"

#define intake_full_power_in()    intake_set_voltage(12800)
#define intake_low_power_out()    intake_set_voltage(-4000)
#define intake_hold_in()          intake_set_voltage(450)
#define intake_stop()             intake_set_voltage(0)

int get_intake_enc(int side = -1);
void intake_set_speed(int speed);
void intake_set_voltage(int mV);
void handle_intake(int key_up, int key_dn, int slow_mode);

extern int intake_dir;

void intake_for_enc_thread(int voltage, int enc_dist, bool wait_for_done=false);
void intake_for_time_thread(int voltage, int msec, bool wait_for_done=false);
void intake_unlock_service();
void intake_unlock_thread_start() ;