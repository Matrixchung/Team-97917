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
#include<string>
#include<cstring>

#include "v5.h"
#include "v5_vcs.h"
#pragma once

typedef struct _pid {
  float range;
  float SetSpeed;
  float ActualSpeed;
  float Err;
  float Err_Last;
  float Kp, Ki, Kd;
  float Voltage;
  float Integral;
} pid;

class pid_control{
    public:
    void PID_init(float p,float i,float d,float range);
    float PID_control(float target_value, float actual_value);
    pid pid;
    private:
};

void setSpeed();
void reset();
void blueback();
void redback();
void mv(int velocity,float cm,bool isCollect);
void release();
vex::task turn(int velocity,float degree);
void stop_all();
void elev();
void protect_blue();
void gyroCalibrate();
void record();
void elevate();
void swingControl();
void arm();
void record();
void FinalAuto();
void LoadAuton();