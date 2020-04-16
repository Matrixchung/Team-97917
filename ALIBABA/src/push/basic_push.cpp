#include "../push/push.h"

int get_push_enc() {
  wait(1);
  return (int)mtr_push.rotation(rotationUnits::raw);
}

void push_enc_reset() { mtr_push.resetRotation(); }

void push_set_speed(int v) {
  // cout << "Vel: " << v << endl;
  mtr_push.spin(directionType::fwd, v, vex::velocityUnits::pct);
}

void push_set_voltage(int mV) {
  // cout << "Vol: " << mV << endl;
  mtr_push.spin(directionType::fwd, mV, voltageUnits::mV);
}
