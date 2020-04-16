#include "vex.h"
#include <list>
#include <algorithm>
#include <fstream>
#include <iostream>
using namespace std;
using namespace vex;
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
        brakeType brakeWay;
        
        dataslice() {
        }
        
        dataslice(uint32_t time, double vel, velocityUnits units, brakeType brake) {
            timestamp = time;
            normalizedVelocity = vel;
            velocityType = units;
            brakeWay=brake;
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
    brakeType brakeWayNow=brake; //默认刹车方式 brake
    
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
            data.emplace_back(invocationTime - operationBeginTime,velocity,units,brakeWayNow);
            lastRecordingTime = invocationTime;
        } else if (myState == playback) {
            if (playbackMarker == data.end()) {
                stop(playbackMarker->brakeWay);
            } else if (invocationTime >= operationBeginTime + playbackMarker->timestamp) {
                motor::spin(directionType::fwd, playbackMarker->normalizedVelocity, playbackMarker->velocityType);
                playbackMarker++;
            }
        } else if (myState == none) {
            motor::spin(dir,velocity,units);
        }
    }
    
    void spin (directionType dir, double velocity, percentUnits units) {
        spin(dir,velocity,velocityUnits::pct);
    }
    void setStopping(brakeType mode)
    {
      brakeWayNow=mode;
    }
    void stop()
    {
      motor::stop();
    }
    void stop(brakeType type)
    {
      motor::setStopping(type);
      spin(directionType::fwd,0,velocityUnits::pct);
    }
    void enableRecording() {
        lastRecordingTime = operationBeginTime = timer::system();
        data.clear();
        data.emplace_back(0,0,velocityUnits::pct,brakeWayNow);
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
        ofstream outputFile(logFileName, ofstream::out | ofstream::trunc);
        for (list<dataslice>::iterator it = data.begin(); it != data.end(); ++it) {
            /*outputFile.write((char*)&(it->timestamp),sizeof(dataslice::timestamp));
            outputFile.write((char*)&(it->normalizedVelocity),sizeof(dataslice::normalizedVelocity));
            outputFile.write((char*)&(it->voltageType),sizeof(dataslice::voltageType));
            outputFile.write((char*)&(it->brakeWay),sizeof(dataslice::brakeWay));*/
            outputFile<<it->timestamp<<" "<<it->normalizedVelocity<<" "<<(char*)&(it->velocityType)<<" "<<(char*)&(it->brakeWay)<<endl;
            outputFile.flush();
        }
        outputFile.close();
    }
    
    void loadRecording () {
        disableRecording();
        data.clear();
        ifstream inputFile(logFileName, ifstream::in);
        while (!inputFile.eof()) {
            dataslice nextInput;
            /*inputFile.read((char*)&(nextInput.timestamp),sizeof(dataslice::timestamp));
            inputFile.read((char*)&(nextInput.normalizedVelocity),sizeof(dataslice::normalizedVelocity));
            inputFile.read((char*)&(nextInput.voltageType),sizeof(dataslice::voltageType));
            inputFile.read((char*)&(nextInput.brakeWay),sizeof(dataslice::brakeWay));*/
            inputFile>>nextInput.timestamp>>nextInput.normalizedVelocity>>(char*)&(nextInput.velocityType)>>(char*)&(nextInput.brakeWay);
            data.push_back(nextInput);
        }
    }
    
    ~velocityRecordedMotor() {}
};
class voltageRecordedMotor : public vex::motor {
    private:
    
    // 数据块结构 - 时间戳、速度、单位(velocityUnits)
    struct dataslice {
        uint32_t timestamp;
        double normalizedVelocity;
        voltageUnits voltageType;
        brakeType brakeWay;
        dataslice() {
        }
        
        dataslice(uint32_t time, double vel, voltageUnits units,brakeType brake) {
            timestamp = time;
            normalizedVelocity = vel;
            voltageType = units;
            brakeWay = brake;
        }
    };
    
    // 双链表储存 - 迭代器 playBackMarker
    std::list<dataslice> data;
    
    // 迭代器循环
    std::list<dataslice>::iterator playbackMarker;
    
    // 文件名
    const char* logFileName;
    brakeType brakeWayNow=brake; //默认刹车方式 brake
    //lastRecordingTime 限制最小计数时间
    uint32_t lastRecordingTime;
    uint32_t operationBeginTime;
    
    // 记录器三个状态常量：{none recording playback}
    enum recordingState {none, recording, playback};
    recordingState myState = none;
    
    public:
    
    // voltageRecordedMotor 继承 vex::motor 类 覆盖 声明类(PORT,gearSetting,isReversed,附加logFileName) spin()
    voltageRecordedMotor (int32_t index, gearSetting gears, bool reversed, const char* logFileName)
      : motor (index,gears,reversed) {
        this->logFileName = logFileName;
        lastRecordingTime = timer::system();
    }
    
    void spin (directionType dir, double voltage, voltageUnits units) {
        uint32_t invocationTime = timer::system();
        if (myState == recording && invocationTime > lastRecordingTime) {
            motor::spin(dir,voltage,units);
            if (dir == directionType::rev) voltage = -voltage;
            data.emplace_back(invocationTime - operationBeginTime,voltage,units,brakeWayNow);
            lastRecordingTime = invocationTime;
        } else if (myState == playback) {
            if (playbackMarker == data.end()) {
                stop(playbackMarker->brakeWay);
            } else if (invocationTime >= operationBeginTime + playbackMarker->timestamp) {
                motor::spin(vex::directionType::fwd, playbackMarker->normalizedVelocity, playbackMarker->voltageType);
                playbackMarker++;
            }
        } else if (myState == none) {
            motor::spin(dir,voltage,units);
        }
    }
    void setStopping(brakeType mode)
    {
      brakeWayNow=mode;
    }
    void stop()
    {
      motor::stop();
    }
    void stop(brakeType type)
    {
      motor::setStopping(type);
      spin(directionType::fwd,0,voltageUnits::mV);
    }
    void enableRecording() {
        lastRecordingTime = operationBeginTime = timer::system();
        data.clear();
        data.emplace_back(0,0,voltageUnits::mV,brakeWayNow);
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
        ofstream outputFile(logFileName, ofstream::out | ofstream::trunc);
        for (list<dataslice>::iterator it = data.begin(); it != data.end(); ++it) {
            /*outputFile.write((char*)&(it->timestamp),sizeof(dataslice::timestamp));
            outputFile.write((char*)&(it->normalizedVelocity),sizeof(dataslice::normalizedVelocity));
            outputFile.write((char*)&(it->voltageType),sizeof(dataslice::voltageType));
            outputFile.write((char*)&(it->brakeWay),sizeof(dataslice::brakeWay));*/
            outputFile<<it->timestamp<<" "<<it->normalizedVelocity<<" "<<(char*)&(it->voltageType)<<" "<<(char*)&(it->brakeWay)<<endl;
            outputFile.flush();
        }
        outputFile.close();
    }
    
    void loadRecording () {
        disableRecording();
        data.clear();
        ifstream inputFile(logFileName, ifstream::in);
        while (!inputFile.eof()) {
            dataslice nextInput;
            /*inputFile.read((char*)&(nextInput.timestamp),sizeof(dataslice::timestamp));
            inputFile.read((char*)&(nextInput.normalizedVelocity),sizeof(dataslice::normalizedVelocity));
            inputFile.read((char*)&(nextInput.voltageType),sizeof(dataslice::voltageType));
            inputFile.read((char*)&(nextInput.brakeWay),sizeof(dataslice::brakeWay));*/
            inputFile>>nextInput.timestamp>>nextInput.normalizedVelocity>>(char*)&(nextInput.voltageType)>>(char*)&(nextInput.brakeWay);
            data.push_back(nextInput);
        }
    }
    
    ~voltageRecordedMotor() {}
};