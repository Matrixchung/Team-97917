#include "vex.h"
#include "recorder.h"
#include "drivetrain.h"
#include "functions.h"
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
void LoadAuton()
{
  allDisableRecordingOrPlayback();
  stopall();
  allLoadRecording();
}
void FinalAuto()
{
  bool t1=true;
  if(t1){
  allDisableRecordingOrPlayback();
            Controller.Screen.setCursor(1,1);
            uint32_t startLoadTime = timer::system();
            Controller.Screen.print("Loading...           ");
            stopall();
            allLoadRecording();
            while (timer::system() < startLoadTime + 50);
            Controller.Screen.clearLine(1);
            t1=false;
  }
  bool Temp=true;
  bool checkForPlaybackEnd=false;
  while (1) {
        
            
        if (Temp) {
            if (!LeftF.isPlayback()&&(!SwingL.isPlayback())&&(!SwingR.isPlayback())&&(!Elev.isPlayback())&&(!Arm.isPlayback())) {
                allDisableRecordingOrPlayback();
                allEnablePlayback();
                Controller.Screen.setCursor(1,1);
                Controller.Screen.print("Auto...        ");
                checkForPlaybackEnd = true;
                Temp=false;
            } else {
                allDisableRecordingOrPlayback();
                Controller.Screen.clearLine(1);
                checkForPlaybackEnd = false;
            }
        
        }
        setSpeed();
        
        if (checkForPlaybackEnd && LeftF.donePlayback() && LeftB.donePlayback()&&RightF.donePlayback()&&RightB.donePlayback()&&SwingL.donePlayback()&&SwingR.donePlayback()&&Elev.donePlayback()&&Arm.donePlayback()) {
            checkForPlaybackEnd = false;
            Controller.Screen.setCursor(1,1);
            Controller.Screen.print("Auton Finished  ");
            allDisablePlayback();
        }
        task::sleep(10);
    }
}