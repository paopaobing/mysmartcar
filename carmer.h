#pragma once

#include <exception>
#include <stdarg.h>
#include <stdio.h>
#include <string.h>

#include <wiringPi.h>
#include <softPwm.h>

class Carmer {

    public :

        Carmer();

        void Init();

        void Up();

        void Down();

    private :

        void servo_pulse(int v_iServoPin, int myangle);

        /*摄像头舵机上下和左右两个自由度的变量*/
        int ServoUpDownPos_;

        /*设置舵机驱动引脚*/
        const int ServoUpDownPin = 13;

        const int speed = 5; //转动速度

} ;
