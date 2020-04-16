float get_gyro();
void resetTheGyro(bool key) ;

void turn_pid_absolute(int aim_final, int time_out,int forward=0,int max_speed=100);
void turn_pid_relative(int aim_relative, int time_out,int forward=0,int max_speed=100);

////////////////  
void forward_enc(int aim_final, int time_out, int turn=0,int max_speed=100);

//////////////////////////
// general function
void lay_cubes_into_zone(bool power_full_intake=false);
void forward_to_postion(int speed, int aim_position_enc,int after_speed=0);

void push_reset_thread();
void push_reset();
void unlock_robot();

void push_reset_thread_start();
void push_straight_auto();

//auto routes
void auto_role_one_1();
void auto_role_one_2();
void auto_role_two_1();
void auto_role_two_2();

#define pause()   while(!Controller.ButtonX.pressing() ) 
