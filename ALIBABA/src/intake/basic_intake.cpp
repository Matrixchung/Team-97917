#include "intake.h"

int get_intake_enc(int side) {
  wait(1);
  if (side == -1)
    return (int)mtr_intake_L.rotation(rotationUnits::raw);
  else
    return (int)mtr_intake_R.rotation(rotationUnits::raw);
}
void intake_enc_reset() { mtr_intake_L.resetRotation(); }

/////////////////////////////
void intake_set_speed(int speed) {
  mtr_intake_L.spin(directionType::fwd, speed, velocityUnits::pct);
  mtr_intake_R.spin(directionType::fwd, speed, velocityUnits::pct);
}

void intake_set_voltage(int mV) {
  mtr_intake_L.spin(directionType::fwd, mV, voltageUnits::mV);
  mtr_intake_R.spin(directionType::fwd, mV, voltageUnits::mV);
}

///////////////////////
void intake_unlock_service() {

  int release_lock_rubber_enc = -1000;

  intake_set_voltage(-12800); // out to unlock
  bool L_ok = false, R_ok = false;
  while (1) {
    if (get_intake_enc(-1) < release_lock_rubber_enc) {
      mtr_intake_L.stop();
      L_ok = true;
    }

    if (get_intake_enc(1) < release_lock_rubber_enc) {
      mtr_intake_R.stop();
      R_ok = true;
    }
    if (L_ok && R_ok)
      break;
    wait(5);
  }
  // intake_set_voltage(12800); // in
}

//
void intake_unlock_thread_start() { vex::thread th(intake_unlock_service); }

////////////////////////////////////////////////////////////////
static int intake_time = 0, intake_voltage = 0;

void intake_for_time_service() {
  intake_set_voltage(intake_voltage);
  wait(intake_time);
  intake_set_voltage(1000);
}

void intake_for_time_thread(int voltage, int msec, bool wait_for_done) {
  intake_voltage = voltage;
  intake_time = msec;
  thread t(intake_for_time_service);
  if (wait_for_done)
    while (t.joinable())
      wait(5);
}
////////////////////////
static int intake_dist = 0;

void intake_for_enc_service() {
  intake_set_voltage(intake_voltage);
  int enc_begin = get_intake_enc();
  while (abs(get_intake_enc() - enc_begin) < abs(intake_dist))
    ;
  intake_set_voltage(1000); // hold up
}

void intake_for_enc_thread(int voltage, int enc_dist, bool wait_for_done) {
  intake_voltage = voltage;
  intake_dist = enc_dist;
  thread t(intake_for_enc_service);
  if (wait_for_done)
    while (t.joinable())
      wait(5);
}
