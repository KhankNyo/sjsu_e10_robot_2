
#include "UserInclude.h"
#include "cmove.h"
#include "cutils.h"



void move(int speed)
{
    SetMotor(MOTOR_LEFT_PORT, speed);
    SetMotor(MOTOR_RIGHT_PORT, -speed);
}

void turn(int speed, int steer)
{
    int left = limit_motor_speed(speed + steer);
    int right = limit_motor_speed(speed - steer);
    SetMotor(MOTOR_LEFT_PORT, left);
    SetMotor(MOTOR_RIGHT_PORT, right);
}

