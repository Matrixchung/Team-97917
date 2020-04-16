#include "vex.h"
#include "recorder.h"

#if(Robot==R_97917G)
/*vex::motor LeftFront = vex::motor(vex::PORT18,vex::gearSetting::ratio18_1,false);
vex::motor LeftBack = vex::motor(vex::PORT9,vex::gearSetting::ratio18_1,false);
vex::motor RightFront = vex::motor(vex::PORT3,vex::gearSetting::ratio18_1,true);
vex::motor RightBack = vex::motor(vex::PORT2,vex::gearSetting::ratio18_1,true);
vex::motor Elevator = vex::motor(vex::PORT12,vex::gearSetting::ratio36_1,true);
vex::motor SwingLeft = vex::motor(vex::PORT10,vex::gearSetting::ratio36_1,false);
vex::motor SwingRight = vex::motor(vex::PORT11,vex::gearSetting::ratio36_1,true);
vex::motor ArmMotor = vex::motor(vex::PORT8,vex::gearSetting::ratio36_1,false);*/
extern brain Brain;
voltageRecordedMotor LeftF(PORT18,gearSetting::ratio18_1,false,"LeftFrontRed.txt");
voltageRecordedMotor LeftB(PORT9,gearSetting::ratio18_1,false,"LeftBackRed.txt");
voltageRecordedMotor RightF(PORT3,gearSetting::ratio18_1,true,"RightFrontRed.txt");
voltageRecordedMotor RightB(PORT2,gearSetting::ratio18_1,true,"RightBackRed.txt");
velocityRecordedMotor Elev(PORT12,gearSetting::ratio36_1,false,"ElevatorRed.txt");
velocityRecordedMotor SwingL(PORT10,gearSetting::ratio36_1,false,"SwingLeftRed.txt");
velocityRecordedMotor SwingR(PORT11,gearSetting::ratio36_1,true,"SwingRightRed.txt");
velocityRecordedMotor Arm(PORT8,gearSetting::ratio36_1,true,"ArmMotorRed.txt");
vex::pot pot1=Brain.ThreeWirePort.A;
vex::brain::sdcard sd;

#endif