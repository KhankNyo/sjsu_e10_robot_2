#ifndef ROBOT_UTILS_H
#define ROBOT_UTILS_H


/* returns the number of elements of a compile-time array */
#define STATIC_ARRAY_SIZE(array) (sizeof(array) / sizeof((array)[0]))

/* returns motor speed in 
 * the range of MOTOR_MAX_SPEED and MOTOR_MIN_SPEED, 
 * see config.h */
int limit_motor_speed(int speed);



#endif /* ROBOT_UTILS_H */

