#include "vex.h"
#include "recorder.h"

#if(Robot==R_97917A)
extern brain Brain;
voltageRecordedMotor LeftF(PORT18,gearSetting::ratio18_1,false,"LeftFrontRed.txt");
voltageRecordedMotor LeftB(PORT9,gearSetting::ratio18_1,false,"LeftBackRed.txt");
voltageRecordedMotor RightF(PORT3,gearSetting::ratio18_1,true,"RightFrontRed.txt");
voltageRecordedMotor RightB(PORT2,gearSetting::ratio18_1,true,"RightBackRed.txt");
velocityRecordedMotor Elev(PORT12,gearSetting::ratio36_1,false,"ElevatorRed.txt");
velocityRecordedMotor SwingL(PORT10,gearSetting::ratio36_1,false,"SwingLeftRed.txt");
velocityRecordedMotor SwingR(PORT11,gearSetting::ratio36_1,true,"SwingRightRed.txt");
velocityRecordedMotor Arm(PORT8,gearSetting::ratio36_1,false,"ArmMotorRed.txt");

#endif