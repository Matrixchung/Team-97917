#include "move.h"

int get_move_enc(int side) {
  wait(1);
  if (side == -1)
    return (int)mtr_LF.rotation(rotationUnits::raw);
  else
    return (int)mtr_RB.rotation(rotationUnits::raw);
}
/////////////////////////////////////////////
void move_enc_reset() {
  mtr_LF.resetRotation();
  mtr_LB.resetRotation();
  mtr_RF.resetRotation();
  mtr_RB.resetRotation();
}
///////////////////////////
void move_motors_brake_mode() {
  mtr_LF.setBrake(brakeType ::brake);
  mtr_LB.setBrake(brakeType ::brake);
  mtr_RF.setBrake(brakeType ::brake);
  mtr_RB.setBrake(brakeType ::brake);
}

void move_motors_float_mode() {
  mtr_LF.setBrake(brakeType ::coast);
  mtr_LB.setBrake(brakeType ::coast);
  mtr_RF.setBrake(brakeType ::coast);
  mtr_RB.setBrake(brakeType ::coast);
}
//////////////////////////////////
void move_LR_set_speed(float vl, float vr) {
  mtr_LF.spin(directionType::fwd, vl, vex::velocityUnits::pct);
  mtr_LB.spin(directionType::fwd, vl, vex::velocityUnits::pct);
  mtr_RF.spin(directionType::fwd, vr, vex::velocityUnits::pct);
  mtr_RB.spin(directionType::fwd, vr, vex::velocityUnits::pct);
}

void move_LR_set_voltage(float vl, float vr) {
  mtr_LF.spin(directionType::fwd, vl, vex::voltageUnits::mV);
  mtr_LB.spin(directionType::fwd, vl, vex::voltageUnits::mV);
  mtr_RF.spin(directionType::fwd, vr, vex::voltageUnits::mV);
  mtr_RB.spin(directionType::fwd, vr, vex::voltageUnits::mV);
}
//////////////////////////////////////////
void move_set_voltage(int forward, int turn) {
  move_LR_set_voltage(forward + turn, forward - turn);
}

void move_set_speed(int forward, int turn) {
  move_LR_set_speed(forward + turn, forward - turn);
}

void move(int forward, int turn) {
  move_LR_set_speed(forward + turn, forward - turn);
}
//////////////////////////////////////////