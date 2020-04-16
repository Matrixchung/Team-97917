// To complete the VEXcode V5 Text project upgrade process, please follow the
// steps below.
// 
// 1. You can use the Robot Configuration window to recreate your V5 devices
//   - including any motors, sensors, 3-wire devices, and controllers.
// 
// 2. All previous code located in main.cpp has now been commented out. You
//   will need to migrate this code to the new "int main" structure created
//   below and keep in mind any new device names you may have set from the
//   Robot Configuration window. 
// 
// If you would like to go back to your original project, a complete backup
// of your original (pre-upgraded) project was created in a backup folder
// inside of this project's folder.

// ---- START VEXCODE CONFIGURED DEVICES ----
// ---- END VEXCODE CONFIGURED DEVICES ----

#include "vex.h"

using namespace vex;

int main() {
  // Initializing Robot Configuration. DO NOT REMOVE!
  vexcodeInit();
  
}

// // ---- START VEXCODE CONFIGURED DEVICES ----
// // Robot Configuration:
// // [Name]               [Type]        [Port(s)]
// // ---- END VEXCODE CONFIGURED DEVICES ----
// #include<vex.h>
// #include "functions.h"
// #include <algorithm>
// using namespace vex;
// 
// vex::controller Controller = vex::controller();
// vex::brain Brain;
// vex::competition Competition;
// 
// void pre_auton( void ) {
//   teamcode_display();
//   //set_pid(1.2,0.02,0.5); //p 比例 ,i 积分 ,d 微分
//   //LoadAuton();
//   //thread picdraw(draw);
//   //Controller.Screen.print("%d",picdraw.hardware_concurrency());
//   //picdraw.detach();
//   //Brain.Screen.drawImageFromFile("1.jpg", 0, 0);
// }
// 
// void autonomous( void ) {
//   LoadAuton();
//   FinalAuto();
//   //redback();
//   //blueback();
// }
// 
// void usercontrol( void ) {
//   allDisableRecordingOrPlayback();
//   //record();
//   //aurec();
//   //pre_auton();
//   //blueback();
//  /*Elevator.resetRotation();
//   reset();
//   task::sleep(100);
//   gyroCalibrate();
//   task::sleep(50);
//   Controller.Screen.clearScreen();
//   turn(20,90);*/
//   //aurec();
//  while (1){
//     thread user(record);
//     user.join();
//    // record();
//     /*Controller.Screen.setCursor(1, 0);
//     Controller.Screen.print("%f",g1.value(rotationUnits::deg));
//     Controller.Screen.setCursor(2, 0);
//     Controller.Screen.print("%d",g2.value(analogUnits::mV));*/
//     //record();
//     //fail_safe_elevator();
//     //fail_safe_arm();
//     //vex::task::sleep(5);
// }
// }
// int main() {
//     pre_auton();
//     Competition.autonomous( autonomous );
//     Competition.drivercontrol( usercontrol );
//     thread tr_display(display);
//     while(1) {
//       vex::task::sleep(1);
//     }      
// }    
// 