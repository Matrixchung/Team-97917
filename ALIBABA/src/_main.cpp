#include "_includes.h"

// system
vex::brain Brain;
vex::controller Controller;
vex::competition Competition;

void display(void) {
  while (1) {
    screen_display_choose();
    sensor_display();
    wait(50);
  }
}

int main() {
  Competition.autonomous(autonomous);
  Competition.drivercontrol(usercontrol);

  pre_auton();
  buttons_init();

  vex::thread th_display(display);
  // vex::thread th_gyro(GyroTask);

  while (1) {
    wait(50);
    special_key_handle();
  }
}
