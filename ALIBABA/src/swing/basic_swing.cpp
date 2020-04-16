#include "swing.h"

int get_swing_enc() {
  wait(1);
  return (int)mtr_swing.rotation(rotationUnits::raw);
}
void swing_enc_reset() { mtr_swing.resetRotation(); }
///////////////////////////////////////////////////////////////////

void swing_set_voltage(int mV) {
  mtr_swing.spin(directionType::fwd, mV, voltageUnits::mV);
}
///////////////////////////////////////////
