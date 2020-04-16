#include "vex.h"
#include <list>
#include <algorithm>
#include <fstream>
#include <iostream>
using namespace vex;
using namespace std;

extern brain Brain;
extern controller Controller;

// 公有方法:
//   继承vex::motor类
//    录制方法
//      enableRecording
//      disableRecording
//      enablePlayback
//      disablePlayback
//      disableRecordingOrPlayback
//    存储/读取各电机二进制数据(每个电机一个文件),便于批量调试自动 - 覆盖现有文件
//      saveRecording
//      loadRecording
//    状态方法
//      isRecording
//      isPlayback
//      donePlayback
//      isIdle

class velocityRecordedMotor : public vex::motor {
    private:
    
    // 数据块结构 - 时间戳、速度、单位(velocityUnits)
    struct dataslice {
        uint32_t timestamp;
        double normalizedVelocity;
        velocityUnits velocityType;
        
        dataslice() {
        }
        
        dataslice(uint32_t time, double vel, velocityUnits units) {
            timestamp = time;
            normalizedVelocity = vel;
            velocityType = units;
        }
    };
    
    // 双链表储存 - 迭代器 playBackMarker
    std::list<dataslice> data;
    
    // 迭代器循环
    std::list<dataslice>::iterator playbackMarker;
    
    // 文件名
    const char* logFileName;
    
    //lastRecordingTime 限制最小计数时间
    uint32_t lastRecordingTime;
    uint32_t operationBeginTime;
    
    // 记录器三个状态常量：{none recording playback}
    enum recordingState {none, recording, playback};
    recordingState myState = none;
    
    public:
    
    // velocityRecordedMotor 继承 vex::motor 类 覆盖 声明类(PORT,gearSetting,isReversed,附加logFileName) spin()
    velocityRecordedMotor (int32_t index, gearSetting gears, bool reversed, const char* logFileName)
      : motor (index,gears,reversed) {
        this->logFileName = logFileName;
        lastRecordingTime = timer::system();
    }
    
    void spin (directionType dir, double velocity, velocityUnits units) {
        uint32_t invocationTime = timer::system();
        if (myState == recording && invocationTime > lastRecordingTime) {
            motor::spin(dir,velocity,units);
            if (dir == directionType::rev) velocity = -velocity;
            data.emplace_back(invocationTime - operationBeginTime,velocity,units);
            lastRecordingTime = invocationTime;
        } else if (myState == playback) {
            if (playbackMarker == data.end()) {
                stop(brakeType::hold);
            } else if (invocationTime >= operationBeginTime + playbackMarker->timestamp) {
                motor::spin(vex::directionType::fwd, playbackMarker->normalizedVelocity, playbackMarker->velocityType);
                playbackMarker++;
            }
        } else if (myState == none) {
            motor::spin(dir,velocity,units);
        }
    }
    
    void spin (directionType dir, double velocity, percentUnits units) {
        spin(dir,velocity,velocityUnits::pct);
    }
    void stop()
    {
      motor:stop();
    }
    void stop(brakeType type)
    {
      motor::setStopping(type);
      spin(directionType::fwd,0,percentUnits::pct);
    }
    void enableRecording() {
        lastRecordingTime = operationBeginTime = timer::system();
        data.clear();
        data.emplace_back(0,0,velocityUnits::pct);
        myState = recording;
    }
    
    bool isRecording() {
        return myState == recording;
    }
    
    bool isPlayback() {
        return myState == playback;
    }
    
    bool donePlayback() {
        return playbackMarker == data.end();
    }
    
    bool isIdle() {
        return myState == none;
    }
    
    void disableRecording() {
        if (myState == recording) {
            myState = none;
        }
    }
    
    void enablePlayback() {
        playbackMarker = data.begin();
        operationBeginTime = timer::system();
        myState = playback;
    }
    
    void disablePlayback() {
        if (myState == playback) {
            myState = none;
        }
    }
    
    void disableRecordingOrPlayback () {
        myState = none;
    }
    
    void saveRecording() {
        disableRecording();
        ofstream outputFile(logFileName, ofstream::out | ofstream::trunc | ofstream::binary); //二进制输出
        for (list<dataslice>::iterator it = data.begin(); it != data.end(); ++it) {
            outputFile.write((char*)&(it->timestamp),sizeof(dataslice::timestamp));
            outputFile.write((char*)&(it->normalizedVelocity),sizeof(dataslice::normalizedVelocity));
            outputFile.write((char*)&(it->velocityType),sizeof(dataslice::velocityType));
            outputFile.flush(); //刷新文件流
        }
        outputFile.close();
    }
    
    void loadRecording () {
        disableRecording();
        data.clear();
        ifstream inputFile(logFileName, ifstream::in | ifstream::binary);
        while (!inputFile.eof()) {
            dataslice nextInput;
            inputFile.read((char*)&(nextInput.timestamp),sizeof(dataslice::timestamp));
            inputFile.read((char*)&(nextInput.normalizedVelocity),sizeof(dataslice::normalizedVelocity));
            inputFile.read((char*)&(nextInput.velocityType),sizeof(dataslice::velocityType));
            data.push_back(nextInput);
        }
    }
    
    ~velocityRecordedMotor() {}
};

//Work in Progress
velocityRecordedMotor LeftF(PORT1,gearSetting::ratio18_1,false,"LeftFrontSkill.txt");
velocityRecordedMotor LeftB(PORT2,gearSetting::ratio18_1,false,"LeftBackSkill.txt");
velocityRecordedMotor RightF(PORT3,gearSetting::ratio18_1,false,"RightFrontSkill.txt");
velocityRecordedMotor RightB(PORT4,gearSetting::ratio18_1,false,"RightBackSkill.txt");
velocityRecordedMotor Elev(PORT8,gearSetting::ratio36_1,true,"ElevatorSkill.txt");
velocityRecordedMotor SwingL(PORT5,gearSetting::ratio36_1,false,"SwingLeftSkill.txt");
velocityRecordedMotor SwingR(PORT6,gearSetting::ratio36_1,true,"SwingRightSkill.txt");
velocityRecordedMotor Arm(PORT7,gearSetting::ratio36_1,true,"ArmMotorSkill.txt");
extern int mainX,mainY;
void stopall()
{
  LeftF.stop();LeftB.stop();RightF.stop();RightB.stop();Elev.stop();SwingL.stop();SwingR.stop();Arm.stop();
}
void setspeed()
{
  if(abs(Controller.Axis4.value())>=20) 
  {
    mainY=Controller.Axis4.value()*0.8;
    if(abs(Controller.Axis3.value())>=20) {mainX=Controller.Axis3.value()*0.9;} else {mainX=0.0;}
  } 
  else {mainY=0.0;}
  if(abs(Controller.Axis3.value())>=20) 
  {
    mainX=Controller.Axis3.value();
  } else {mainX=0.0;}
  if(Controller.ButtonUp.pressing()==Controller.ButtonDown.pressing()){
      LeftF.spin(directionType::fwd,(mainX+mainY),velocityUnits::pct);
      LeftB.spin(directionType::fwd,(mainX+mainY),velocityUnits::pct);
      RightF.spin(directionType::fwd,(mainY-mainX),velocityUnits::pct);
      RightB.spin(directionType::fwd,(mainY-mainX),velocityUnits::pct);
  }
  else if(Controller.ButtonUp.pressing()) {LeftF.spin(directionType::fwd,20,velocityUnits::pct);
  LeftB.spin(directionType::fwd,20,velocityUnits::pct);
  RightF.spin(directionType::rev,20,velocityUnits::pct);
  RightB.spin(directionType::rev,20,velocityUnits::pct);}
  else if(Controller.ButtonDown.pressing()) {LeftF.spin(directionType::rev,20,velocityUnits::pct);
  LeftB.spin(directionType::rev,20,velocityUnits::pct);
  RightF.spin(directionType::fwd,20,velocityUnits::pct);
  RightB.spin(directionType::fwd,20,velocityUnits::pct);}
}
void swControl()
{
  if(Controller.ButtonR1.pressing()==Controller.ButtonR2.pressing()) {SwingL.spin(directionType::rev,0,velocityUnits::pct);SwingR.spin(directionType::rev,0,velocityUnits::pct);}
  else if(Controller.ButtonR2.pressing()) {SwingL.spin(directionType::rev,127,velocityUnits::pct);SwingR.spin(directionType::rev,127,velocityUnits::pct);}
  else if(Controller.ButtonR1.pressing()) {SwingL.spin(directionType::fwd,127,velocityUnits::pct);SwingR.spin(directionType::fwd,127,velocityUnits::pct);}
}
void am()
{
  if(Controller.ButtonL2.pressing()) {Arm.spin(directionType::fwd,127,velocityUnits::pct);}
  else if(Controller.ButtonL1.pressing()) {Arm.spin(directionType::rev,70,velocityUnits::pct);}
  else if(Controller.ButtonL1.pressing()==Controller.ButtonL2.pressing()) {Arm.spin(directionType::rev,0,velocityUnits::pct);}
}
extern int elevateValue;
void elevat()
{
  if(abs(Controller.Axis2.value())>=10) {
    if(Controller.Axis2.value()>=10) {elevateValue=Controller.Axis2.value()*0.4;}
    else if(Controller.Axis2.value()<=-10) {elevateValue=Controller.Axis2.value();}
    Elev.spin(directionType::fwd,elevateValue,velocityUnits::pct);
    }
  else if(abs(Controller.Axis2.value())<10){
    elevateValue=0;
    Elev.spin(directionType::fwd,elevateValue,velocityUnits::pct);
  }
}
void record() {
    SwingL.setBrake(brakeType::hold);
    SwingR.setBrake(brakeType::hold);
    Elev.setBrake(brakeType::hold);
    Arm.setBrake(brakeType::hold);
    bool AlastPressed = false;
    bool BlastPressed = false;
    bool XlastPressed = false;
    bool YlastPressed = false;
    bool checkForPlaybackEnd = false;
    while (1) {
        if (!AlastPressed && Controller.ButtonA.pressing()) {
            if (!LeftF.isRecording()&&(!SwingL.isRecording())&&(!SwingR.isRecording())&&(!Elev.isRecording())&&(!Arm.isRecording())) {
                LeftF.disableRecordingOrPlayback();
                LeftB.disableRecordingOrPlayback();
                RightF.disableRecordingOrPlayback();
                RightB.disableRecordingOrPlayback();
                SwingL.disableRecordingOrPlayback();
                SwingR.disableRecordingOrPlayback();
                Elev.disableRecordingOrPlayback();
                Arm.disableRecordingOrPlayback();
                LeftF.enableRecording();
                LeftB.enableRecording();
                RightF.enableRecording();
                RightB.enableRecording();
                SwingL.enableRecording();
                SwingR.enableRecording();
                Elev.enableRecording();
                Arm.enableRecording();
                Controller.Screen.setCursor(1,1);
                Controller.Screen.print("Recording...         ");
            } else {
                LeftF.disableRecordingOrPlayback();
                LeftB.disableRecordingOrPlayback();
                RightF.disableRecordingOrPlayback();
                RightB.disableRecordingOrPlayback();
                SwingL.disableRecordingOrPlayback();
                SwingR.disableRecordingOrPlayback();
                Elev.disableRecordingOrPlayback();
                Arm.disableRecordingOrPlayback();
                Controller.Screen.clearLine(1);
            }
            AlastPressed = true;
        } else if (!BlastPressed && Controller.ButtonB.pressing()) {
            if (!LeftF.isPlayback()&&(!SwingL.isPlayback())&&(!SwingR.isPlayback())&&(!Elev.isPlayback())&&(!Arm.isPlayback())) {
                LeftF.disableRecordingOrPlayback();
                LeftB.disableRecordingOrPlayback();
                RightF.disableRecordingOrPlayback();
                RightB.disableRecordingOrPlayback();
                SwingL.disableRecordingOrPlayback();
                SwingR.disableRecordingOrPlayback();
                Elev.disableRecordingOrPlayback();
                Arm.disableRecordingOrPlayback();
                LeftF.enablePlayback();
                LeftB.enablePlayback();
                RightF.enablePlayback();
                RightB.enablePlayback();
                SwingL.enablePlayback();
                SwingR.enablePlayback();
                Elev.enablePlayback();
                Arm.enablePlayback();
                Controller.Screen.setCursor(1,1);
                Controller.Screen.print("Playback...        ");
                checkForPlaybackEnd = true;
            } else {
                LeftF.disableRecordingOrPlayback();
                LeftB.disableRecordingOrPlayback();
                RightF.disableRecordingOrPlayback();
                RightB.disableRecordingOrPlayback();
                SwingL.disableRecordingOrPlayback();
                SwingR.disableRecordingOrPlayback();
                Elev.disableRecordingOrPlayback();
                Arm.disableRecordingOrPlayback();
                Controller.Screen.clearLine(1);
                checkForPlaybackEnd = false;
            }
            BlastPressed = true;
        } else if (!XlastPressed && Controller.ButtonX.pressing()) {
            LeftF.disableRecordingOrPlayback();
            LeftB.disableRecordingOrPlayback();
            RightF.disableRecordingOrPlayback();
            RightB.disableRecordingOrPlayback();
            SwingL.disableRecordingOrPlayback();
            SwingR.disableRecordingOrPlayback();
            Elev.disableRecordingOrPlayback();
            Arm.disableRecordingOrPlayback();
            Controller.Screen.setCursor(1,1);
            uint32_t startLoadTime = timer::system();
            Controller.Screen.print("Saving...           ");
            stopall();
            LeftF.saveRecording();
            LeftB.saveRecording();
            RightF.saveRecording();
            RightB.saveRecording();
            SwingL.saveRecording();
            SwingR.saveRecording();
            Elev.saveRecording();
            Arm.saveRecording();
            while (timer::system() < startLoadTime + 1000); 
            Controller.Screen.clearLine(1);
            XlastPressed = true;
        } else if (!YlastPressed && Controller.ButtonY.pressing()) {
            LeftF.disableRecordingOrPlayback();
            LeftB.disableRecordingOrPlayback();
            RightF.disableRecordingOrPlayback();
            RightB.disableRecordingOrPlayback();
            SwingL.disableRecordingOrPlayback();
            SwingR.disableRecordingOrPlayback();
            Elev.disableRecordingOrPlayback();
            Arm.disableRecordingOrPlayback();
            Controller.Screen.setCursor(1,1);
            uint32_t startLoadTime = timer::system();
            Controller.Screen.print("Loading...           ");
            stopall();
            LeftF.loadRecording();
            LeftB.loadRecording();
            RightF.loadRecording();
            RightB.loadRecording();
            SwingL.loadRecording();
            SwingR.loadRecording();
            Elev.loadRecording();
            Arm.loadRecording();
            while (timer::system() < startLoadTime + 1000);
            Controller.Screen.clearLine(1);
            YlastPressed = true;
        }
        AlastPressed = AlastPressed && Controller.ButtonA.pressing();
        BlastPressed = BlastPressed && Controller.ButtonB.pressing();
        XlastPressed = XlastPressed && Controller.ButtonX.pressing();
        YlastPressed = YlastPressed && Controller.ButtonY.pressing();
        
        swControl();
        setspeed();
        elevat();
        am();
        
        if (checkForPlaybackEnd && LeftF.donePlayback() && LeftB.donePlayback()&&RightF.donePlayback()&&RightB.donePlayback()&&SwingL.donePlayback()&&SwingR.donePlayback()&&Elev.donePlayback()&&Arm.donePlayback()) {
            checkForPlaybackEnd = false;
            Controller.Screen.setCursor(1,1);
            Controller.Screen.print("PlayBack Finished  ");
            LeftF.disablePlayback();
            LeftB.disablePlayback();
            RightF.disablePlayback();
            RightB.disablePlayback();
            SwingL.disablePlayback();
            SwingR.disablePlayback();
            Elev.disablePlayback();
            Arm.disablePlayback();
        }
        task::sleep(20);
    }
}
void LoadAuton()
{
  LeftF.disableRecordingOrPlayback();
    LeftB.disableRecordingOrPlayback();
            RightF.disableRecordingOrPlayback();
            RightB.disableRecordingOrPlayback();
            SwingL.disableRecordingOrPlayback();
            SwingR.disableRecordingOrPlayback();
            Elev.disableRecordingOrPlayback();
            Arm.disableRecordingOrPlayback();
  stopall();
            LeftF.loadRecording();
            LeftB.loadRecording();
            RightF.loadRecording();
            RightB.loadRecording();
            SwingL.loadRecording();
            SwingR.loadRecording();
            Elev.loadRecording();
            Arm.loadRecording();
}
void FinalAuto()
{
  bool t1=true;
  if(t1){
  LeftF.disableRecordingOrPlayback();
            LeftB.disableRecordingOrPlayback();
            RightF.disableRecordingOrPlayback();
            RightB.disableRecordingOrPlayback();
            SwingL.disableRecordingOrPlayback();
            SwingR.disableRecordingOrPlayback();
            Elev.disableRecordingOrPlayback();
            Arm.disableRecordingOrPlayback();
            Controller.Screen.setCursor(1,1);
            uint32_t startLoadTime = timer::system();
            Controller.Screen.print("Loading...           ");
            stopall();
            LeftF.loadRecording();
            LeftB.loadRecording();
            RightF.loadRecording();
            RightB.loadRecording();
            SwingL.loadRecording();
            SwingR.loadRecording();
            Elev.loadRecording();
            Arm.loadRecording();
            while (timer::system() < startLoadTime + 50);
            Controller.Screen.clearLine(1);
            t1=false;
  }
  bool Temp=true;
  bool checkForPlaybackEnd=false;
  //release();
  while (1) {
        
            
        if (Temp) {
            if (!LeftF.isPlayback()&&(!SwingL.isPlayback())&&(!SwingR.isPlayback())&&(!Elev.isPlayback())&&(!Arm.isPlayback())) {
                LeftF.disableRecordingOrPlayback();
                LeftB.disableRecordingOrPlayback();
                RightF.disableRecordingOrPlayback();
                RightB.disableRecordingOrPlayback();
                SwingL.disableRecordingOrPlayback();
                SwingR.disableRecordingOrPlayback();
                Elev.disableRecordingOrPlayback();
                Arm.disableRecordingOrPlayback();
                LeftF.enablePlayback();
                LeftB.enablePlayback();
                RightF.enablePlayback();
                RightB.enablePlayback();
                SwingL.enablePlayback();
                SwingR.enablePlayback();
                Elev.enablePlayback();
                Arm.enablePlayback();
                Controller.Screen.setCursor(1,1);
                Controller.Screen.print("Playback...        ");
                checkForPlaybackEnd = true;
                Temp=false;
            } else {
                LeftF.disableRecordingOrPlayback();
                LeftB.disableRecordingOrPlayback();
                RightF.disableRecordingOrPlayback();
                RightB.disableRecordingOrPlayback();
                SwingL.disableRecordingOrPlayback();
                SwingR.disableRecordingOrPlayback();
                Elev.disableRecordingOrPlayback();
                Arm.disableRecordingOrPlayback();
                Controller.Screen.clearLine(1);
                checkForPlaybackEnd = false;
            }
        
        }
        swControl();
        setspeed();
        elevat();
        am();
        
        if (checkForPlaybackEnd && LeftF.donePlayback() && LeftB.donePlayback()&&RightF.donePlayback()&&RightB.donePlayback()&&SwingL.donePlayback()&&SwingR.donePlayback()&&Elev.donePlayback()&&Arm.donePlayback()) {
            checkForPlaybackEnd = false;
            Controller.Screen.setCursor(1,1);
            Controller.Screen.print("PlayBack Finished  ");
            LeftF.disablePlayback();
            LeftB.disablePlayback();
            RightF.disablePlayback();
            RightB.disablePlayback();
            SwingL.disablePlayback();
            SwingR.disablePlayback();
            Elev.disablePlayback();
            Arm.disablePlayback();
        }
        task::sleep(20);
    }
}