#include "car.h"

//初始化4个轮子
void Car::Init()
{
    now_state = Car::STOP;

    //初始化电机驱动IO口为输出方式
    pinMode(Car::Left_motor_go, OUTPUT);
    pinMode(Car::Left_motor_back, OUTPUT);
    pinMode(Car::Right_motor_go, OUTPUT);
    pinMode(Car::Right_motor_back, OUTPUT);

    //创建两个软件控制的PWM脚
    //int softPwmCreate(int pin,int initialValue,int pwmRange);
    softPwmCreate(Car::Left_motor_pwm,0,255);
    softPwmCreate(Car::Right_motor_pwm,0,255);
}


void Car::run()
{
    if (now_state == Car::RUN)
        return ;
    now_state = RUN;

    //左电机前进
    digitalWrite(Car::Left_motor_go, HIGH);   //左电机前进使能
    digitalWrite(Car::Left_motor_back, LOW);  //左电机后退禁止
    softPwmWrite(Car::Left_motor_pwm, 100);   //PWM比例0-255调速，左右轮差异略增减

    //右电机前进
    digitalWrite(Car::Right_motor_go, HIGH);  //右电机前进使能
    digitalWrite(Car::Right_motor_back, LOW); //右电机后退禁止
    softPwmWrite(Car::Right_motor_pwm, 100);  //PWM比例0-255调速，左右轮差异略增减
}

/**
* Function       brake
* @author        Danny
* @date          2017.08.16
* @brief         小车刹车
* @param[in]     time
* @param[out]    void
* @retval        void
* @par History   无
*/
void Car::stop()
{
    if (now_state == Car::STOP)
        return ;
    now_state = Car::STOP;

    digitalWrite(Car::Left_motor_go, LOW);
    digitalWrite(Car::Left_motor_back, LOW);
    digitalWrite(Car::Right_motor_go, LOW);
    digitalWrite(Car::Right_motor_back, LOW);
}


void Car::left()
{
    if (now_state == Car::LEFT)
        return ;
    now_state = Car::LEFT;

    //左电机停止
    digitalWrite(Car::Left_motor_go, LOW);     //左电机前进禁止
    digitalWrite(Car::Left_motor_back, LOW);   //左电机后退禁止
    softPwmWrite(Car::Left_motor_pwm, 0);      //左边电机速度设为0(0-255)

    //右电机前进
    digitalWrite(Car::Right_motor_go, HIGH);  //右电机前进使能
    digitalWrite(Car::Right_motor_back, LOW); //右电机后退禁止
    softPwmWrite(Car::Right_motor_pwm, 50);  //右边电机速度设200(0-255)
}

void Car::turn_left()
{
    if (now_state == Car::TURNLEFT)
        return ;
    now_state = Car::TURNLEFT;

    //左电机停止
    digitalWrite(Car::Left_motor_go, HIGH);
    digitalWrite(Car::Left_motor_back, LOW);
    softPwmWrite(Car::Left_motor_pwm, 70);      //左边电机速度设为0(0-255)

    //右电机前进
    digitalWrite(Car::Right_motor_go, HIGH);
    digitalWrite(Car::Right_motor_back, LOW);
    softPwmWrite(Car::Right_motor_pwm, 100);  //右边电机速度设200(0-255)
}



void Car::right()
{
    if (now_state == Car::RIGHT)
        return ;
    now_state = Car::RIGHT;

    //左电机前进
    digitalWrite(Car::Left_motor_go, HIGH);    //左电机前进使能
    digitalWrite(Car::Left_motor_back, LOW);   //左电机后退禁止
    softPwmWrite(Car::Left_motor_pwm, 50);    //左边电机速度设200(0-255)

    //右电机停止
    digitalWrite(Car::Right_motor_go, LOW);    //右电机前进禁止
    digitalWrite(Car::Right_motor_back, LOW);  //右电机后退禁止
    softPwmWrite(Car::Right_motor_pwm, 0);     //右边电机速度设0(0-255)
}

void Car::turn_right()
{
    if (now_state == Car::TURNRIGHT)
        return ;
    now_state = Car::TURNRIGHT;

    //左电机前进
    digitalWrite(Car::Left_motor_go, HIGH);
    digitalWrite(Car::Left_motor_back, LOW);
    softPwmWrite(Car::Left_motor_pwm, 100);    //左边电机速度设200(0-255)

    //右电机停止
    digitalWrite(Car::Right_motor_go, HIGH);
    digitalWrite(Car::Right_motor_back, LOW);
    softPwmWrite(Car::Right_motor_pwm, 70);     //右边电机速度设0(0-255)
}


void Car::back()
{
    if (now_state == Car::BACK)
        return ;
    now_state = Car::BACK;

    //左电机后退
    digitalWrite(Car::Left_motor_go, LOW);     //左电机前进禁止
    digitalWrite(Car::Left_motor_back, HIGH);  //左电机后退使能
    softPwmWrite(Car::Left_motor_pwm, 100);

    //右电机后退
    digitalWrite(Car::Right_motor_go, LOW);    //右电机前进禁止
    digitalWrite(Car::Right_motor_back, HIGH); //右电机后退使能
    softPwmWrite(Car::Right_motor_pwm, 100);

}

//
// void Car::spin_left()
// {
//   //左电机后退
//   digitalWrite(Car::Left_motor_go, LOW);    //左电机前进禁止
//   digitalWrite(Car::Left_motor_back, HIGH); //左电机后退使能
//   softPwmWrite(Car::Left_motor_pwm, 50);
//
//   //右电机前进
//   digitalWrite(Car::Right_motor_go, HIGH);  //右电机前进使能
//   digitalWrite(Car::Right_motor_back, LOW); //右电机后退禁止
//   softPwmWrite(Car::Right_motor_pwm, 50);
// }
//
// void Car::spin_right()
// {
//   //左电机前进
//   digitalWrite(Car::Left_motor_go, HIGH);    //左电机前进使能
//   digitalWrite(Car::Left_motor_back, LOW);   //左电机后退禁止
//   softPwmWrite(Car::Left_motor_pwm, 50);
//
//   //右电机后退
//   digitalWrite(Car::Right_motor_go, LOW);    //右电机前进禁止
//   digitalWrite(Car::Right_motor_back, HIGH); //右电机后退使能
//   softPwmWrite(Car::Right_motor_pwm, 50);
//
// }
