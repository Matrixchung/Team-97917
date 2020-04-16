#include<cmath>
#include<vex.h>
using namespace std;
void pid_control::PID_init(float p,float i,float d,float range)
{
  pid.range=range;
  pid.SetSpeed = 0;
  pid.ActualSpeed = 0;
  pid.Err = 0;
  pid.Err_Last = 0;
  pid.Kp = p;
  pid.Ki = i;
  pid.Kd = d;
  pid.Voltage = 0;
  pid.Integral = 0;
}

float pid_control::PID_control(float target_value, float actual_value){
  /*if(target_value==0.0)
  {
    pid.SetSpeed=0.0;
    pid.ActualSpeed=0.0;
    return 0;
  }
  else{*/
  //pid.ActualSpeed=(actual_value/pid.range)*200.0;
  pid.ActualSpeed=actual_value*200.0;
  pid.SetSpeed = (target_value / pid.range) * 200.0;
  //if(pid.SetSpeed>=200.0) {pid.SetSpeed=200.0;} else if(pid.SetSpeed<=-200.0) {pid.SetSpeed=-200.0;}
  pid.Err = pid.SetSpeed - pid.ActualSpeed;
  pid.Integral += pid.Err;
  pid.Voltage = pid.Kp * pid.Err + pid.Ki * pid.Integral +
                pid.Kd * (pid.Err - pid.Err_Last);
  if(pid.Voltage>=200.0) {pid.Voltage=200.0;} if(pid.Voltage<=-200.0) {pid.Voltage=-200.0;}
  pid.Err_Last = pid.Err;
  return (pid.Voltage/200.0)*12.0;
  }
