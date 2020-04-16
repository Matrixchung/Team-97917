#include "Globals.h"

void reset_all_encoders() {
  mtr_LF.resetRotation();
  mtr_LB.resetRotation();
  mtr_RF.resetRotation();
  mtr_RB.resetRotation();
  mtr_swing.resetRotation();
  mtr_push.resetRotation();
  mtr_intake_L.resetRotation();
  mtr_intake_R.resetRotation();
}

bool b_all_motor_float = false;
bool b_all_motor_already_brake = false;

void all_motor_brake() {
  if (b_all_motor_float)
    return;

  if (b_all_motor_already_brake) {
    // cout << "already brake" << endl;
    return;
  } else
    b_all_motor_already_brake = true;

  mtr_LF.setBrake(brakeType ::brake);
  mtr_LB.setBrake(brakeType ::brake);
  mtr_RF.setBrake(brakeType ::brake);
  mtr_RB.setBrake(brakeType ::brake);
  mtr_swing.setBrake(brakeType ::brake);
  mtr_push.setBrake(brakeType ::brake);
  mtr_intake_L.setBrake(brakeType ::brake);
  mtr_intake_R.setBrake(brakeType ::brake);
}

void all_motors_float() {
  //b_all_motor_already_brake = false;
  cout << "coast.." << endl;
  mtr_LF.setBrake(brakeType ::coast);
  mtr_LB.setBrake(brakeType ::coast);
  mtr_RF.setBrake(brakeType ::coast);
  mtr_RB.setBrake(brakeType ::coast);
  mtr_swing.setBrake(brakeType ::coast);
  mtr_push.setBrake(brakeType ::coast);
  mtr_intake_L.setBrake(brakeType ::coast);
  mtr_intake_R.setBrake(brakeType ::coast);
}

void stop_all_motors() {
  mtr_LF.spin(directionType::fwd, 0, voltageUnits::mV);
  mtr_LB.spin(directionType::fwd, 0, voltageUnits::mV);
  mtr_RF.spin(directionType::fwd, 0, voltageUnits::mV);
  mtr_RB.spin(directionType::fwd, 0, voltageUnits::mV);
  mtr_swing.spin(directionType::fwd, 0, voltageUnits::mV);
  mtr_push.spin(directionType::fwd, 0, voltageUnits::mV);
  mtr_intake_L.spin(directionType::fwd, 0, voltageUnits::mV);
  mtr_intake_R.spin(directionType::fwd, 0, voltageUnits::mV);
}