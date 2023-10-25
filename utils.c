

#include "config.h"
#include "utils.h"



int limit_motor_speed(int speed)
{
    if (speed > MOTOR_MAX_SPEED)
        speed = MOTOR_MAX_SPEED;
    else if (speed < MOTOR_MIN_SPEED)
        speed = MOTOR_MIN_SPEED;
    return speed;
}

