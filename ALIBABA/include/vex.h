/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       vex.h                                                     */
/*    Author:       Vex Robotics                                              */
/*    Created:      1 Feb 2019                                                */
/*    Description:  Default header for V5 projects                            */
/*                                                                            */
/*----------------------------------------------------------------------------*/
//
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "iostream"
#include "robot-config.h"
#include "v5.h"
#include "v5_vcs.h"

#define R_Normal 0
#define R_74000M 1
#define R_74000V 2
#define R_74000P 3
#define R_74000F 4
#define R_77921F 5


#define ROBOT    R_74000V

 
/*
User defined function
*/
using namespace vex;
using namespace std;

//gloabl 
extern vex::brain       Brain;
extern vex::controller  Controller;
extern vex::competition Competition;


#define Print Brain.Screen.printAt
// #define wait   vex::this_thread::sleep_for
void wait(int milsec);
#define delay wait

void pre_auton(void);
void autonomous(void);
void usercontrol(void);

#define abs(x) (((x) > 0) ? (x) : -(x))
int sgn(double x);
void zero_blind(int &x, unsigned int threshold);
void max_limit(int &x, unsigned int bnd);