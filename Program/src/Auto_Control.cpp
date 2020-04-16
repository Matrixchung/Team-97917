#include <vex.h>
#include<cmath>
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

pid_control autonl;
pid_control autonr;
void set_pid_auton(float p,float i,float d)
{
  autonl.PID_init(p,i,d,360.0);
  autonr.PID_init(p,i,d,360.0);
}
void collect()
{
  SwingLeft.spin(directionType::fwd,12,voltageUnits::volt);SwingRight.spin(directionType::fwd,12,voltageUnits::volt);
}
void mv(int velocity,float cm,bool isCollect)
{
  float degree=(cm/25.933846913)*360.0;
  reset();
  if(isCollect==true){
  collect();
  LeftFront.startRotateFor(1,degree,rotationUnits::deg,velocity,velocityUnits::pct);
  LeftBack.startRotateFor(2,degree,rotationUnits::deg,velocity,velocityUnits::pct);
  RightFront.startRotateFor(3,-degree,rotationUnits::deg,-velocity,velocityUnits::pct);
  RightBack.rotateFor(-degree,rotationUnits::deg,-velocity,velocityUnits::pct);
  }
  else {
  SwingLeft.stop(brakeType::coast);SwingRight.stop(brakeType::coast);
  LeftFront.startRotateFor(1,degree,rotationUnits::deg,velocity,velocityUnits::pct);
  LeftBack.startRotateFor(2,degree,rotationUnits::deg,velocity,velocityUnits::pct);
  RightFront.startRotateFor(3,-degree,rotationUnits::deg,-velocity,velocityUnits::pct);
  RightBack.rotateFor(-degree,rotationUnits::deg,-velocity,velocityUnits::pct);
  }
}
void release()
{
  /*Elevator.setTimeout(3, timeUnits::sec);
  ArmMotor.setTimeout(3, timeUnits::sec);
  Elevator.rotateFor(120,rotationUnits::deg,520,velocityUnits::pct);
  task::sleep(100);
  ArmMotor.rotateFor(380,rotationUnits::deg,520,velocityUnits::pct);
  task::sleep(500);
  Elevator.rotateFor(-100,rotationUnits::deg,520,velocityUnits::pct);
  ArmMotor.startRotateFor(-400,rotationUnits::deg,520,velocityUnits::pct);
  task::sleep(50);*/
  Elevator.spinFor(250,timeUnits::msec,520,velocityUnits::rpm);
  task::sleep(10);
  Elevator.spinFor(200,timeUnits::msec,520,velocityUnits::rpm);
  task::sleep(50);
  ArmMotor.spinFor(110,timeUnits::msec,520,velocityUnits::rpm);
  task::sleep(160);
  Elevator.spinFor(10,timeUnits::msec,520,velocityUnits::rpm);
  task::sleep(80);
  ArmMotor.startRotateFor(60,rotationUnits::deg,520,velocityUnits::pct);
  Elevator.startRotateFor(-800,rotationUnits::deg,520,velocityUnits::pct);
  task::sleep(80);
  ArmMotor.startRotateFor(-80,rotationUnits::deg,520,velocityUnits::pct);
  task::sleep(80);
  ArmMotor.rotateFor(90,rotationUnits::deg,520,velocityUnits::pct);
  ArmMotor.startRotateFor(-90,rotationUnits::deg,520,velocityUnits::pct);
  task::sleep(50);
  Elevator.startRotateFor(-500,rotationUnits::deg,520,velocityUnits::pct);
}
void gyroCalibrate()
{
  g1.startCalibration();
  g2.startCalibration();
  while(g1.isCalibrating()==true||g2.isCalibrating()==true)
  {
    task::sleep(1);
  }
  task::sleep(100);
}
float gyro1=0.0,gyro2=0.0;
float gyroCurrent=0.0;
float gyroErr=0.0;
float gyroValue()
{
   gyro1=g1.angle(rotationUnits::deg)-5.0;
   gyro2=g2.angle(rotationUnits::deg)-5.0;
  if(abs(gyro1-gyroErr)<=abs(gyro2-gyroErr))
  {
    gyroCurrent=gyro1;
  }
  else{gyroCurrent=gyro2;}
  gyroErr=gyroCurrent;
  if(gyroCurrent>360.0)
  {gyroCurrent = gyroCurrent-360.0;}
  else if(gyroCurrent<-360.0)
  {gyroCurrent = gyroCurrent+360.0;}
  return gyroCurrent;
}
float target=0.0;
/*
while(std::abs(target-gyroValue())>=2&&maxLimit<=2000)
{
  if(degree>0.0)
  {
    LeftFront.spin(directionType::fwd,autonl.PID_control(target-gyroValue(),LeftFront.velocity(velocityUnits::rpm)),voltageUnits::volt);
  }
}
*/
task turn(int velocity,float degree)
{
  int maxLimit=0;
  collect();  //gyro calibrates with +-5 degrees
  target=degree+gyroValue();
  if(target>360)
  {target = target-360;}
  else if(target<-360)
  {target = target+360;}
  while(std::abs(target-gyroValue())>=1&&maxLimit<=2000)
  {
    if(degree>0.0)
    {
      LeftFront.spin(directionType::fwd,velocity,velocityUnits::pct);
      LeftBack.spin(directionType::fwd,velocity,velocityUnits::pct);
      RightFront.spin(directionType::fwd,velocity,velocityUnits::pct);
      RightBack.spin(directionType::fwd,velocity,velocityUnits::pct);
      Controller.Screen.print("%f",g1.angle(rotationUnits::deg));
    }
    if(degree<0.0)
    {
      LeftFront.spin(directionType::rev,velocity,velocityUnits::pct);
      LeftBack.spin(directionType::rev,velocity,velocityUnits::pct);
      RightFront.spin(directionType::rev,velocity,velocityUnits::pct);
      RightBack.spin(directionType::rev,velocity,velocityUnits::pct);
    }
    maxLimit++;
    vex::task::sleep(1);
  }
  LeftFront.stop(brakeType::brake);
  LeftBack.stop(brakeType::brake);
  RightFront.stop(brakeType::brake);
  RightBack.stop(brakeType::brake);
  LeftFront.setStopping(brakeType::coast);
  LeftBack.setStopping(brakeType::coast);
  RightFront.setStopping(brakeType::coast);
  RightBack.setStopping(brakeType::coast);
  target=0.0;
  return 0;
}
void stop_all()
{
  LeftFront.stop(brakeType::brake);
  LeftBack.stop(brakeType::brake);
  RightFront.stop(brakeType::brake);
  RightBack.stop(brakeType::brake);
}
void elev()
{
  Elevator.spinFor(100,timeUnits::msec,-50,velocityUnits::pct);
  Elevator.resetRotation();
  //max 825
  Elevator.rotateFor(directionType::fwd, 180, rotationUnits::deg,100,velocityUnits::pct);
  Elevator.rotateFor(directionType::fwd, 130, rotationUnits::deg,80,velocityUnits::pct);
  //SwingLeft.startRotateFor(directionType::rev,20,rotationUnits::deg);
  //SwingRight.startRotateFor(directionType::rev,20,rotationUnits::deg);
  Elevator.rotateFor(directionType::fwd, 115, rotationUnits::deg,50,velocityUnits::pct);
  Elevator.stop(brakeType::hold);
}