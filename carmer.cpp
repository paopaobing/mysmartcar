#include "carmer.h"

Carmer::Carmer()
{
    ServoUpDownPos_ = 130; //初始化摄像头位置
}

/**
* Function       servo_pulse
* @author        Danny
* @date          2017.08.16
* @brief         定义一个脉冲函数，用来模拟方式产生PWM值
*                时基脉冲为20ms,该脉冲高电平部分在0.5-2.5ms
*                控制0-180度
* @param[in1]    ServPin:舵机控制引脚
* @param[in2]    myangle:舵机转动指定的角度
* @param[out]    void
* @retval        void
* @par History   无
*/
void Carmer::servo_pulse(int v_iServoPin, int myangle)
{
  int PulseWidth;                    //定义脉宽变量
  PulseWidth = (myangle * 11) + 500; //将角度转化为500-2480 的脉宽值
  digitalWrite(v_iServoPin, HIGH);      //将舵机接口电平置高
  delayMicroseconds(PulseWidth);     //延时脉宽值的微秒数
  digitalWrite(v_iServoPin, LOW);       //将舵机接口电平置低
  delay(20 - PulseWidth / 1000);     //延时周期内剩余时间
  return;
}


void Carmer::Init()
{
    pinMode(Carmer::ServoUpDownPin, OUTPUT);

	for (int i = 0; i < 10; i++)
        servo_pulse(Carmer::ServoUpDownPin, ServoUpDownPos_);
}

void Carmer::Up()
{
    ServoUpDownPos_ += speed;
    if (ServoUpDownPos_ >= 180)
        ServoUpDownPos_ = 180;
	servo_pulse(Carmer::ServoUpDownPin, ServoUpDownPos_); //模拟产生PWM
}

void Carmer::Down()
{
    ServoUpDownPos_ -= speed;
    if (ServoUpDownPos_ <= 35)
        ServoUpDownPos_ = 35;
   	servo_pulse(Carmer::ServoUpDownPin, ServoUpDownPos_); //模拟产生PWM
}
