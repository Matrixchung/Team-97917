#include "vex.h"
#include "drivetrain.h"
#include "recorder.h"
using namespace std;
using namespace vex;
extern controller Controller;
extern voltageRecordedMotor LeftF;
extern voltageRecordedMotor LeftB;
extern voltageRecordedMotor RightF;
extern voltageRecordedMotor RightB;
extern velocityRecordedMotor Arm;
extern velocityRecordedMotor Elev;
extern velocityRecordedMotor SwingL;
extern velocityRecordedMotor SwingR;
extern pot pot1;
bool fwdIntake=false;
bool revIntake=false;
bool fwdPush=false;
bool revPush=false;
void intake()
{
  if(Robot == R_97917G)
  {
    fwdIntake=Controller.ButtonR1.pressing();
    revIntake=Controller.ButtonR2.pressing();
  }
  if((fwdIntake==0&&revIntake==0)||(fwdIntake&&revIntake))
  {
    SwingL.stop(brakeType::hold);
    SwingR.stop(brakeType::hold);
  }
  else if(fwdIntake)
  {
    SwingL.spin(directionType::fwd, 500, velocityUnits::pct);
    SwingR.spin(directionType::fwd, 500, velocityUnits::pct);
  }
  else if(revIntake)
  {
    SwingL.spin(directionType::rev, 500, velocityUnits::pct);
    SwingR.spin(directionType::rev, 500, velocityUnits::pct);  
  }
}
short elevDegree=0,elevInit=0;
void push()
{
  if(Robot == R_97917G)
  {
    if(elevInit==0)
    {
      elevInit=pot1.value(rotationUnits::deg);
    }
    elevDegree=pot1.value(rotationUnits::deg)-elevInit;
    fwdPush=Controller.ButtonL1.pressing();
    revPush=Controller.ButtonL2.pressing();
  }
  if((fwdPush==0&&revPush==0)||(fwdPush&&revPush))
  {
    Elev.stop(brakeType::hold);
  }
  else if(fwdPush)
  {
    if(elevDegree>-20)
    {Elev.spin(directionType::fwd, 127, velocityUnits::pct);}
    else if(elevDegree>-50) {Elev.spin(directionType::fwd, 60, velocityUnits::pct);}
    else if(elevDegree<-50){Elev.spin(directionType::fwd, 20, velocityUnits::pct);}
    else if(elevDegree<-55){Elev.spin(directionType::fwd,10,velocityUnits::pct);}
  }
  else if(revPush)
  {
    Elev.spin(directionType::rev, 100, velocityUnits::pct);
  }
}
short armMeter=0;
void arm()
{
  if(Robot == R_97917G)
  {
    armMeter=Controller.Axis2.value();
  }
  if(abs(armMeter)>10)
  {
    Arm.spin(directionType::fwd,armMeter,velocityUnits::pct);
  }
  else {Arm.stop(brakeType::hold);}
}