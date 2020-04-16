/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       vex.h                                                     */
/*    Author:       Matrixchung                                               */
/*    Created:      1 Oct 2019                                                */
/*    Description:  Default header for V5 projects                            */
/*                                                                            */
/*----------------------------------------------------------------------------*/
//
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include<algorithm>
#include<string>
#include<cstring>

#include "v5.h"
#include "v5_vcs.h"
#pragma once

#define Robot R_97917G
#define R_97917A 1
#define R_97917G 2


void setSpeed();
void reset();
void blueback();
void redback();
void mv(int velocity,float cm,bool isCollect);
void release();
vex::task turn(int velocity,float degree);
void stop_all();
void elev();
void gyroCalibrate();
void record();
void elevate();
void swingControl();
void arm();
void record();
void FinalAuto();
void LoadAuton();
void allDisableRecordingOrPlayback();
void teamcode_display();

void all_motor_brake();

int sgn(double x);
void wait(int milsec);
void zero_blind(int &x, unsigned int threshold);
void max_limit(int &x, unsigned int bnd);
//Autonomous Selector Initialize Begins
#define SIDE_RED  -1
#define SIDE_BLUE  1

#define ROLE_ONE      1
#define ROLE_TWO    2

#define ROLE_ONE_MAX_AUTO_NUMBER 2
#define ROLE_TWO_MAX_AUTO_NUMBER 2

class AutoInfor {
  public:
  int side;
  int role;
  int route_number;
  AutoInfor(int s, int r,int n):side(s), role(r),route_number(n){}
};

extern AutoInfor auto_info;
//Autonomous Selector Initialize Ends

#include "robot-config.h"

#define waitUntil(condition)                                                   \
  do {                                                                         \
    wait(5, msec);                                                             \
  } while (!(condition))

#define repeat(iterations)                                                     \
  for (int iterator = 0; iterator < iterations; iterator++)