#include "../src/_includes.h"

void BatteryChange(bool key_1) {
  if(key_1){
  
  push_set_speed(100);
  while (limit_push_max)
    ;
  swing_set_voltage(12800);
  while (get_swing_enc() < 1000)
    ;
  }
}
