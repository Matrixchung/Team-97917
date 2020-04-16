#include <vex.h>
using namespace vex;
using namespace std;

extern brain Brain;
extern motor LeftFront;
extern motor LeftBack;
extern motor RightFront;
extern motor RightBack;
extern motor Elevator;
extern motor SwingLeft;
extern motor SwingRight;
extern motor ArmMotor;
extern controller Controller;
extern gyro g1;
extern gyro g2;
void blueback()
{
  LeftFront.setTimeout(1,timeUnits::sec);
  LeftBack.setTimeout(1,timeUnits::sec);
  RightFront.setTimeout(1,timeUnits::sec);
  RightBack.setTimeout(1,timeUnits::sec);
  LeftFront.spin(directionType::fwd,-127,velocityUnits::pct);
  LeftBack.spin(directionType::fwd,-127,velocityUnits::pct);
  RightFront.spin(directionType::fwd,127,velocityUnits::pct);
  RightBack.spin(directionType::fwd,127,velocityUnits::pct);
  task::sleep(200);
  LeftFront.stop(brakeType::coast);
  LeftBack.stop(brakeType::coast);
  RightFront.stop(brakeType::coast);
  RightBack.stop(brakeType::coast);
  Elevator.stop(brakeType::brake);
  SwingLeft.setStopping(brakeType::coast);
  SwingRight.setStopping(brakeType::coast);
  reset();
  task::sleep(50);
  mv(85,183,true); //123 all +60
  task::sleep(50);
  mv(35,-23,true);
  task::sleep(10);
  turn(30,19);
  SwingLeft.stop();
  SwingRight.stop();
  task::sleep(100);
  mv(80,-173,true);
  task::sleep(200);
  turn(50,-18);
  task::sleep(100);
  mv(80,177,true);
  task::sleep(100);
  SwingLeft.stop();
  SwingRight.stop();
  //turn(35,-144);
  task::sleep(300);
  //Elevator.startRotateFor(100,rotationUnits::deg,127,velocityUnits::pct);
  mv(80,30,false); //temp
 // mv(127,90,false);
  /*task::sleep(100);
  SwingLeft.startRotateFor(directionType::rev,290,rotationUnits::deg);
  SwingRight.startRotateFor(directionType::rev,290,rotationUnits::deg);
  task::sleep(100);
  elev();
  task::sleep(100);
  mv(8,4,false);
  task::sleep(100);
  //SwingLeft.startRotateFor(directionType::fwd,120,rotationUnits::deg);
  //SwingRight.startRotateFor(directionType::fwd,120,rotationUnits::deg);
  task::sleep(200);
  mv(127,-50,false);*/

}