#pragma once

#include <exception>
#include <stdarg.h>
#include <stdio.h>
#include <string.h>

#include <wiringPi.h>
#include <softPwm.h>

class Car
{
    public :

        void Init();

        void run();

        void stop();

        void left();
        void turn_left();

        void right();
        void turn_right();


        // void spin_left();
        //
        // void spin_right();

        void back();

    private :

        enum State {
            RUN,
            STOP,
            LEFT,
            TURNLEFT,
            TURNRIGHT,
            RIGHT,
            BACK
        } now_state;

        //定义引脚
        const int Left_motor_go = 28;       //左电机前进AIN2连接Raspberry的wiringPi编码28口
        const int Left_motor_back = 29;     //左电机后退AIN1连接Raspberry的wiringPi编码29口

        const int Right_motor_go = 24;      //右电机前进BIN2连接Raspberry的wiringPi编码24口
        const int Right_motor_back = 25;    //右电机后退BIN1连接Raspberry的wiringPi编码25口

        const int Left_motor_pwm = 27;      //左电机控速PWMA连接Raspberry的wiringPi编码27口
        const int Right_motor_pwm = 23;     //右电机控速PWMB连接Raspberry的wiringPi编码23口

};
