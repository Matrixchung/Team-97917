#include "vex.h"
#include "recorder.h"
#include "drivetrain.h"
#include "functions.h"
using namespace vex;
using namespace std;

extern brain Brain;
extern controller Controller;
extern pot JD1;

extern voltageRecordedMotor LeftF;
extern voltageRecordedMotor LeftB;
extern voltageRecordedMotor RightF;
extern voltageRecordedMotor RightB;
extern velocityRecordedMotor Arm;
extern velocityRecordedMotor Elev;
extern velocityRecordedMotor SwingL;
extern velocityRecordedMotor SwingR;

int X1G, Y1G, X2G, Y2G;     // Graph of OP
    int modelA = 1, modelB = 1; // Select menu
    int ln = 3;                 //遥控标准误差
    //设定摇杆控制的最大速度
    double Max_MovingSpeed_pct = 100, Max_RotatingSpeed_pct = 80; //直行和转弯
    double Max_LaunchSpeed_rpm = 60, Max_LeftSpeed_pct = 100,
           Max_SuckSpeed = 100; //
    /*FORMULAS:Rotational speed formula:MaxR*PCT=RPM;Travelling speed
     * formula:Size*2.54*3.14*PRM/60=Speed;(cm/s)*/

    double p1 = 0.0038, p2 = 0.0030; // It may change;Working for OPS.

    /*Marker variables & Settings*/
    double refresh;                      // Screen refresh time
    int Leftmotors_pct, Rightmotors_pct; //同侧轮速度控制
    double pp = 0.6;
    double Maxdeg5 = 14, Mini5 = 55, Maxdeg6 = 1000; // 5和6号电机的推出限位装置
          double TCSD;
          int RCM = 0; //双圈循环
    int SCSC, NAxis4;
    int Controller_Axis3=0,Controller_Axis4=0;
    int CA3=0,CA4=0;
    double s1=0,s2=0;


void stopall()
{
  LeftF.stop();LeftB.stop();RightF.stop();RightB.stop();Elev.stop();SwingL.stop();SwingR.stop();Arm.stop();
}
bool bSlowMode=false;
double MD5=0;
bool L1=0,L2=0;
int x=0;
short Controller_Axis2=0;
int xis2=0;
void setSpeed()
{
  
      if (b_all_motor_float == false) {

        // cout << "try to brakr..." << endl;
        all_motor_brake();
        // b_all_motor_already_brake = true;
      }
      bSlowMode=Controller.ButtonUp.pressing();
      handle_move(Controller.Axis3.position(), Controller.Axis4.position(),
                  bSlowMode);
      intake();
      arm();
      push();
      /*// 推出装置的控制
      // double MD5 = Elev.rotation(rotationUnits::deg); //旋转角度
      MD5 = JD1.value(percentUnits::pct);
      L1 = Controller.ButtonL1.pressing();
      L2 = Controller.ButtonL2.pressing();

      if (MD5 <= Maxdeg5 || MD5 >= Mini5) {
        if (MD5 <= Maxdeg5) {
          Elev.startRotateFor(-4, rotationUnits::deg, Max_LaunchSpeed_rpm,
                                velocityUnits::pct);
        }
        if (MD5 >= Mini5) {
          Elev.startRotateTo(4, rotationUnits::deg, Max_LaunchSpeed_rpm,
                               velocityUnits::pct);
        }
      } else { 
        if (L1 == 1 || L2 == 1) {
          if (L1 == 1) { //推出
            x = JD1.value(percentUnits::pct);
            TCSD = -0.00006062824403808663 * x * x * x * x +
                   0.004729491070475326 * x * x * x -
                   0.05311071797139716 * x * x - 0.18966127285763013 * x +
                   14.0;
            Elev.spin(directionType::fwd, TCSD, velocityUnits::rpm);
          }
          if (L2 == 1) { //收回
            Elev.spin(directionType::rev, Max_LaunchSpeed_rpm,
                        velocityUnits::rpm);
          }
        } else {
          Elev.stop(brakeType::hold);
        }
      }

      //手臂控制
     

      Arm.spin(directionType::fwd, xis2, velocityUnits::pct); //第二选择（取消保护后）
      if (xis2 == 0) {
        Arm.stop(brakeType::hold);
      }

     */
}

void record() {
    bool AlastPressed = false;
    bool BlastPressed = false;
    bool XlastPressed = false;
    bool YlastPressed = false;
    bool checkForPlaybackEnd = false;
    bool isInserted=true;
    while (1) {
      if(Brain.SDcard.isInserted()==false) {
        if(isInserted) {
        Controller.Screen.setCursor(1,1); 
        Controller.Screen.print("Not Inserted!!");
        isInserted=false;
        }
      }
      else{
        if(isInserted==false) {Controller.Screen.clearLine(1);isInserted=true;}
        if (!AlastPressed && Controller.ButtonA.pressing()) {
            if (!LeftF.isRecording()&&(!SwingL.isRecording())&&(!SwingR.isRecording())&&(!Elev.isRecording())&&(!Arm.isRecording())) {
                
                allDisableRecordingOrPlayback();
                allEnableRecording();

                Controller.Screen.setCursor(1,1);
                
                Controller.Screen.print("Recording...         ");
            } else {
                allDisableRecordingOrPlayback();
                Controller.Screen.clearLine(1);
            }
            
            AlastPressed = true;
        } else if (!BlastPressed && Controller.ButtonB.pressing()) {
            if (!LeftF.isPlayback()&&(!SwingL.isPlayback())&&(!SwingR.isPlayback())&&(!Elev.isPlayback())&&(!Arm.isPlayback())) {
                allDisableRecordingOrPlayback();
                allEnablePlayback();
                Controller.Screen.setCursor(1,1);
                
                Controller.Screen.print("Playback...        ");
                checkForPlaybackEnd = true;
            } else {
                allDisableRecordingOrPlayback();
                Controller.Screen.clearLine(1);
                checkForPlaybackEnd = false;
            }
            BlastPressed = true;
        } else if (!XlastPressed && Controller.ButtonX.pressing()) {
            allDisableRecordingOrPlayback();
            Controller.Screen.setCursor(1,1);
            
            uint32_t startLoadTime = timer::system();
            Controller.Screen.print("Saving...           ");
            stopall();
            allSaveRecording();
            while (timer::system() < startLoadTime + 1000); 
            Controller.Screen.clearLine(1);
            XlastPressed = true;
        } else if (!YlastPressed && Controller.ButtonY.pressing()) {
            allDisableRecordingOrPlayback();
            Controller.Screen.setCursor(1,1);
            
            uint32_t startLoadTime = timer::system();
            Controller.Screen.print("Loading...           ");
            stopall();
            allLoadRecording();
            while (timer::system() < startLoadTime + 1000);
            Controller.Screen.clearLine(1);
            YlastPressed = true;
        }
        AlastPressed = AlastPressed && Controller.ButtonA.pressing();
        BlastPressed = BlastPressed && Controller.ButtonB.pressing();
        XlastPressed = XlastPressed && Controller.ButtonX.pressing();
        YlastPressed = YlastPressed && Controller.ButtonY.pressing();
        
        setSpeed();
        //LeftF.donePlayback() && LeftB.donePlayback()&&RightF.donePlayback()&&RightB.donePlayback()&&SwingL.donePlayback()&&SwingR.donePlayback()&&Elev.donePlayback()&&Arm.donePlayback()
        if (checkForPlaybackEnd&&LeftF.donePlayback() && LeftB.donePlayback()&&RightF.donePlayback()&&RightB.donePlayback()&&SwingL.donePlayback()&&SwingR.donePlayback()&&Elev.donePlayback()&&Arm.donePlayback()) {
            checkForPlaybackEnd = false;
            Controller.Screen.setCursor(1,1);
            Controller.Screen.print("PlayBack Finished ");
            allDisablePlayback();
        }
        task::sleep(5);
    }}
}
