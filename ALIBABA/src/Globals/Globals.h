#pragma once

#include "vex.h"

extern vex::motor mtr_LF;
extern vex::motor mtr_LB;
extern vex::motor mtr_RF;
extern vex::motor mtr_RB;
extern vex::motor mtr_intake_L;
extern vex::motor mtr_intake_R;

extern vex::motor mtr_swing;
extern vex::motor mtr_push;
//sensors
extern vex::gyro gyro_z;

extern vex::limit limit_push_max;
extern vex::limit limit_push_min;
//////////////////////////////////////////////



//global varibls
extern bool bSlowMode;

//do not modify
#define SIDE_RED  -1
#define SIDE_BLUE  1

#define ROLE_ONE      1
#define ROLE_TWO    2

#define ROLE_ONE_MAX_AUTO_NUMBER 2
#define ROLE_TWO_MAX_AUTO_NUMBER 2

class AutoInfor {
  public:
  int side;///红蓝
  int role;///1还是2区
  int route_number;///线路号
  AutoInfor(int s, int r,int n):side(s), role(r),route_number(n){}
};

extern AutoInfor auto_info;

extern bool auto_testing;
extern bool b_all_motor_float;
extern bool b_all_motor_already_brake;

void all_motor_brake();
void all_motors_float();
void stop_all_motors();

void reset_all_encoders();
//////////////////////////////////////////////
