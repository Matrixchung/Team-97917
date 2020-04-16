#include "recorder.h"
#include "drivetrain.h"
extern voltageRecordedMotor LeftF;
extern voltageRecordedMotor LeftB;
extern voltageRecordedMotor RightF;
extern voltageRecordedMotor RightB;
extern velocityRecordedMotor Arm;
extern velocityRecordedMotor Elev;
extern velocityRecordedMotor SwingL;
extern velocityRecordedMotor SwingR;
//////////////////////////////////////////
void move_set_voltage(int forward, int turn) {
  move_LR_set_voltage(forward + turn, forward - turn);
}

//////////////////////////////////////////
void reset_all_encoders() {
  LeftF.resetRotation();
  LeftB.resetRotation();
  RightF.resetRotation();
  RightB.resetRotation();
  Arm.resetRotation();
  Elev.resetRotation();
  SwingL.resetRotation();
  SwingR.resetRotation();
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

  LeftF.setBrake(brakeType ::brake);
  LeftB.setBrake(brakeType ::brake);
  RightF.setBrake(brakeType ::brake);
  RightB.setBrake(brakeType ::brake);
  Arm.setBrake(brakeType ::brake);
  Elev.setBrake(brakeType ::brake);
  SwingL.setBrake(brakeType ::brake);
  SwingR.setBrake(brakeType ::brake);
}

void all_motors_float() {
  //b_all_motor_already_brake = false;
  cout << "coast.." << endl;
  LeftF.setBrake(brakeType ::coast);
  LeftB.setBrake(brakeType ::coast);
  RightF.setBrake(brakeType ::coast);
  RightB.setBrake(brakeType ::coast);
  Arm.setBrake(brakeType ::coast);
  Elev.setBrake(brakeType ::coast);
  SwingL.setBrake(brakeType ::coast);
  SwingR.setBrake(brakeType ::coast);
}

void stop_all_motors() {
  LeftF.spin(directionType::fwd, 0, voltageUnits::mV);
  LeftB.spin(directionType::fwd, 0, voltageUnits::mV);
  RightF.spin(directionType::fwd, 0, voltageUnits::mV);
  RightB.spin(directionType::fwd, 0, voltageUnits::mV);
  Arm.spin(directionType::fwd, 0, velocityUnits::pct);
  Elev.spin(directionType::fwd, 0, velocityUnits::pct);
  SwingL.spin(directionType::fwd, 0, velocityUnits::pct);
  SwingR.spin(directionType::fwd, 0, velocityUnits::pct);
}
int get_move_enc(int side) {
  wait(1);
  if (side == -1)
    return (int)LeftF.rotation(rotationUnits::raw);
  else
    return (int)RightB.rotation(rotationUnits::raw);
}
/////////////////////////////////////////////
void move_enc_reset() {
  LeftF.resetRotation();
  LeftB.resetRotation();
  RightF.resetRotation();
  RightB.resetRotation();
}
///////////////////////////
void move_motors_brake_mode() {
  LeftF.setBrake(brakeType ::brake);
  LeftB.setBrake(brakeType ::brake);
  RightF.setBrake(brakeType ::brake);
  RightB.setBrake(brakeType ::brake);
}

void move_motors_float_mode() {
  LeftF.setBrake(brakeType ::coast);
  LeftB.setBrake(brakeType ::coast);
  RightF.setBrake(brakeType ::coast);
  RightB.setBrake(brakeType ::coast);
}
//////////////////////////////////

void move_LR_set_voltage(float vl, float vr) {
  LeftF.spin(directionType::fwd, vl, vex::voltageUnits::mV);
  LeftB.spin(directionType::fwd, vl, vex::voltageUnits::mV);
  RightF.spin(directionType::fwd, vr, vex::voltageUnits::mV);
  RightB.spin(directionType::fwd, vr, vex::voltageUnits::mV);
}
void allEnableRecording()
{
  LeftF.enableRecording();
  LeftB.enableRecording();
  RightF.enableRecording();
  RightB.enableRecording();
  SwingL.enableRecording();
  SwingR.enableRecording();
  Elev.enableRecording();
  Arm.enableRecording();
}
void allDisableRecordingOrPlayback()
{
  LeftF.disableRecordingOrPlayback();
  LeftB.disableRecordingOrPlayback();
  RightF.disableRecordingOrPlayback();
  RightB.disableRecordingOrPlayback();
  SwingL.disableRecordingOrPlayback();
  SwingR.disableRecordingOrPlayback();
  Elev.disableRecordingOrPlayback();
  Arm.disableRecordingOrPlayback();
}
void allEnablePlayback()
{
  LeftF.enablePlayback();
  LeftB.enablePlayback();
  RightF.enablePlayback();
  RightB.enablePlayback();
  SwingL.enablePlayback();
  SwingR.enablePlayback();
  Elev.enablePlayback();
  Arm.enablePlayback();
}
void allSaveRecording()
{            
  LeftF.saveRecording();
  LeftB.saveRecording();
  RightF.saveRecording();
  RightB.saveRecording();
  SwingL.saveRecording();
  SwingR.saveRecording();
  Elev.saveRecording();
  Arm.saveRecording();
}
void allLoadRecording()
{
  LeftF.loadRecording();
  LeftB.loadRecording();
  RightF.loadRecording();
  RightB.loadRecording();
  SwingL.loadRecording();
  SwingR.loadRecording();
  Elev.loadRecording();
  Arm.loadRecording();
}
void allDisablePlayback()
{
  LeftF.disablePlayback();
  LeftB.disablePlayback();
  RightF.disablePlayback();
  RightB.disablePlayback();
  SwingL.disablePlayback();
  SwingR.disablePlayback();
  Elev.disablePlayback();
  Arm.disablePlayback();
}