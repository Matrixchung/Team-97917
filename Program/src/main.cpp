/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       Matrixchung                                               */
/*    Created:      15 Oct 2019                                               */
/*    Description:  Main Loop for VEX 97917A                                  */
/*                                                                            */
/*----------------------------------------------------------------------------*/
//Smart Ports using RS285 Serial 
#include<vex.h>
#include<bits/stdc++.h>
#include <algorithm>
using namespace vex;
#define AUTON_NONE 0
#define AUTON_RED_BACK 1
#define AUTON_RED_FRONT 2
#define AUTON_BLUE_BACK 3
#define AUTON_BLUE_FRONT 4
vex::controller Controller = vex::controller();
vex::brain Brain;
vex::competition Competition;
vex::motor LeftFront = vex::motor(vex::PORT1,vex::gearSetting::ratio18_1,false);
vex::motor LeftBack = vex::motor(vex::PORT2,vex::gearSetting::ratio18_1,false);
vex::motor RightFront = vex::motor(vex::PORT3,vex::gearSetting::ratio18_1,false);
vex::motor RightBack = vex::motor(vex::PORT4,vex::gearSetting::ratio18_1,false);
vex::motor Elevator = vex::motor(vex::PORT8,vex::gearSetting::ratio36_1,true);
vex::motor SwingLeft = vex::motor(vex::PORT5,vex::gearSetting::ratio36_1,false);
vex::motor SwingRight = vex::motor(vex::PORT6,vex::gearSetting::ratio36_1,true);
vex::motor ArmMotor = vex::motor(vex::PORT7,vex::gearSetting::ratio36_1,true);
vex::brain::sdcard sd;

pid_control pidl;
pid_control pidr;
void set_pid(float p,float i,float d)
{
  pidl.PID_init(p,i,d,200.0);
  pidr.PID_init(p,i,d,200.0);
}
void reset()  
{
  LeftFront.resetRotation();
  LeftBack.resetRotation();
  RightFront.resetRotation();
  RightBack.resetRotation();
}
float mainX=0.0,mainY=0.0;
const float thresholdX=30.0,thresholdY=30.0;
int elevateValue=0;
void swingControl()
{
  if(Controller.ButtonR2.pressing()) {SwingLeft.spin(directionType::rev,666,velocityUnits::pct);SwingRight.spin(directionType::rev,666,velocityUnits::pct);}
  else if(Controller.ButtonR1.pressing()) {SwingLeft.spin(directionType::fwd,666,velocityUnits::pct);SwingRight.spin(directionType::fwd,666,velocityUnits::pct);}
  else if(Controller.ButtonR1.pressing()==Controller.ButtonR2.pressing()) {SwingLeft.stop(brakeType::hold);SwingRight.stop(brakeType::hold);}
}
void arm()
{
  if(Controller.ButtonL2.pressing()) {ArmMotor.spin(directionType::fwd,114514,velocityUnits::pct);}
  else if(Controller.ButtonL1.pressing()) {ArmMotor.spin(directionType::rev,70,velocityUnits::pct);}
  else if(Controller.ButtonL1.pressing()==Controller.ButtonL2.pressing()) {ArmMotor.stop(brakeType::hold);}
}
void elevate()
{
  if(abs(Controller.Axis2.value())>=10) {
    if(Controller.Axis2.value()>=10) {elevateValue=Controller.Axis2.value()*0.4;}
    else if(Controller.Axis2.value()<=-10) {elevateValue=Controller.Axis2.value();}
    Elevator.spin(directionType::fwd,elevateValue,velocityUnits::pct);
    }
  else if(abs(Controller.Axis2.value())<10){
    elevateValue=0;
    Elevator.stop(brakeType::hold);
  }
}
bool isLowSpeed=false;
void setSpeed()
{
  if(abs(Controller.Axis4.value())>=thresholdY) 
  {
    mainY=((Controller.Axis4.value()/127.0)*200.0)*0.8;
    if(abs(Controller.Axis3.value())>=thresholdX) {mainX=((Controller.Axis3.value()/127.0)*200.0)*0.9;} else {mainX=0.0;}
  } 
  else {mainY=0.0;}
  if(abs(Controller.Axis3.value())>=thresholdX) 
  {
    mainX=((Controller.Axis3.value()/127.0)*200.0);
  } else {mainX=0.0;}
  if(Controller.ButtonA.pressing()) {isLowSpeed=!isLowSpeed;vex::task::sleep(200);}
  if(Controller.ButtonUp.pressing()==Controller.ButtonDown.pressing()){
    /*if(isLowSpeed==false)
    {
      LeftFront.spin(directionType::fwd,pidl.PID_control(mainX+mainY,LeftFront.velocity(velocityUnits::rpm)),voltageUnits::volt);
      LeftBack.spin(directionType::fwd,pidl.PID_control(mainX+mainY,LeftFront.velocity(velocityUnits::rpm)),voltageUnits::volt);
      RightFront.spin(directionType::fwd,pidr.PID_control(mainY-mainX,RightFront.velocity(velocityUnits::rpm)),voltageUnits::volt);
      RightBack.spin(directionType::fwd,pidr.PID_control(mainY-mainX,RightFront.velocity(velocityUnits::rpm)),voltageUnits::volt);
    }*/
    if(isLowSpeed==false)
    {
      LeftFront.spin(directionType::fwd,(mainX+mainY),velocityUnits::rpm);
      LeftBack.spin(directionType::fwd,(mainX+mainY),velocityUnits::rpm);
      RightFront.spin(directionType::fwd,(mainY-mainX),velocityUnits::rpm);
      RightBack.spin(directionType::fwd,(mainY-mainX),velocityUnits::rpm);
    }
    else if(isLowSpeed==true)
    {
      LeftFront.spin(directionType::fwd,(mainX+mainY)*0.6,velocityUnits::rpm);
      LeftBack.spin(directionType::fwd,(mainX+mainY)*0.6,velocityUnits::rpm);
      RightFront.spin(directionType::fwd,(mainY-mainX)*0.6,velocityUnits::rpm);
      RightBack.spin(directionType::fwd,(mainY-mainX)*0.6,velocityUnits::rpm);
    }
  }
  else if(Controller.ButtonUp.pressing()) {LeftFront.spin(directionType::fwd,20,velocityUnits::pct);
  LeftBack.spin(directionType::fwd,20,velocityUnits::pct);
  RightFront.spin(directionType::rev,20,velocityUnits::pct);
  RightBack.spin(directionType::rev,20,velocityUnits::pct);}
  else if(Controller.ButtonDown.pressing()) {LeftFront.spin(directionType::rev,20,velocityUnits::pct);
  LeftBack.spin(directionType::rev,20,velocityUnits::pct);
  RightFront.spin(directionType::fwd,20,velocityUnits::pct);
  RightBack.spin(directionType::fwd,20,velocityUnits::pct);} 
  vex::task::sleep(10);
}
void pre_auton( void ) {
  //set_pid(1.2,0.02,0.5); //p 比例 ,i 积分 ,d 微分
  LeftFront.setMaxTorque(500,percentUnits::pct);
  LeftBack.setMaxTorque(500,percentUnits::pct);
  RightFront.setMaxTorque(500,percentUnits::pct);
  RightBack.setMaxTorque(500,percentUnits::pct);
  Elevator.setMaxTorque(500, percentUnits::pct);
  SwingLeft.setMaxTorque(500, percentUnits::pct);
  SwingRight.setMaxTorque(500, percentUnits::pct);
  ArmMotor.setMaxTorque(500, percentUnits::pct);
  LeftFront.setBrake(brakeType::coast);
  LeftBack.setBrake(brakeType::coast);
  RightFront.setBrake(brakeType::coast);
  RightBack.setBrake(brakeType::coast);
  SwingLeft.setBrake(brakeType::coast);
  SwingRight.setBrake(brakeType::coast);
  reset();
  //LoadAuton();
  //thread picdraw(draw);
  //Controller.Screen.print("%d",picdraw.hardware_concurrency());
  //picdraw.detach();
  //Brain.Screen.drawImageFromFile("1.jpg", 0, 0);
}

void autonomous( void ) {
  LoadAuton();
  FinalAuto();
  //redback();
  //blueback();
  //aurec();
}
void userC()
{
  setSpeed();
  elevate();
  arm();
  swingControl();
  //record();
}
void usercontrol( void ) {
  record();
  //aurec();
  //pre_auton();
  //blueback();
 /*Elevator.resetRotation();
  reset();
  task::sleep(100);
  gyroCalibrate();
  task::sleep(50);
  Controller.Screen.clearScreen();
  turn(20,90);*/
  //aurec();
 /*while (1){
    thread user(userC);
    user.join();}*/
    //record();
    /*Controller.Screen.setCursor(1, 0);
    Controller.Screen.print("%f",g1.value(rotationUnits::deg));
    Controller.Screen.setCursor(2, 0);
    Controller.Screen.print("%d",g2.value(analogUnits::mV));*/
    //record();
    //fail_safe_elevator();
    //fail_safe_arm();
    //vex::task::sleep(5);
//}
}
int main() {
    pre_auton();
    Competition.autonomous( autonomous );
    Competition.drivercontrol( usercontrol );
    while(1) {
      vex::task::sleep(1);
    }      
}    
