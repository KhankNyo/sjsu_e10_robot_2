
#include "config.h"
#include "move.h"
#include "utils.h"



void move(int speed)
{
    SetMotor(MOTOR_LEFT_PORT, speed);
    SetMotor(MOTOR_RIGHT_PORT, -speed);
}

void turn(int steer, int speed)
{
    int left = limit_motor_speed(steer + speed);
    int right = limit_motor_speed(steer - speed);
    SetMotor(MOTOR_LEFT_PORT, left);
    SetMotor(MOTOR_RIGHT_PORT, right);
}


