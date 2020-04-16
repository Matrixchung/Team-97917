#include "vex.h"

#if (ROBOT == R_77921F)
// move
vex::motor mtr_LF(vex::PORT6, false);
vex::motor mtr_LB(vex::PORT2, false);
vex::motor mtr_RF(vex::PORT11, true);
vex::motor mtr_RB(vex::PORT12, true);

// intake
vex::motor mtr_intake_L(vex::PORT4, vex::ratio36_1, false);
vex::motor mtr_intake_R(vex::PORT15, vex::ratio36_1, true);

// other
vex::motor mtr_swing(vex::PORT13, vex::ratio36_1, false);
vex::motor mtr_push(vex::PORT17, vex::ratio36_1, false);

// sensors
vex::gyro gyro_z(Brain.ThreeWirePort.B);
vex::limit limit_push_max(Brain.ThreeWirePort.A);

#endif