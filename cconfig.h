#ifndef ROBOT_CONFIG_H
#define ROBOT_CONFIG_H


/* states */
#define STATE_FIND_RED 1
#define STATE_TURN_OFF_RED 2
#define STATE_FIND_GREEN 3
#define STATE_CAPTURE_GREEN 4
#define STATE_GO_HOME 5
#define STATE_EXIT 0xff


/* misc */
#define AMBIENT_LEVEL 200
#define PD_MIDDLE 4
#define PD_GREEN_BEACON_MODE 0
#define PD_RED_BEACON_MODE 1
#define NEVER_STOP (((unsigned)1 << (sizeof(int)*8 - 1)) - 1) /* int_max */
#define MIN_DIST_TO_WALL 4



/* speed and handling */
#define FORWARD_SPEED 40
#define SPIN_SPEED 20
#define FAST_SPIN_SPEED 50
#define SLOW_SPEED 20
#define STEER_SENSITIVITY 20

#define MOTOR_MAX_SPEED 127
#define MOTOR_MIN_SPEED -128


/* arm */
#define ARM_UP 0
#define ARM_DOWN 127


/* ports */
#define ARM_SERVO_PORT 2

#define LIMIT_SWITCH_PORT 5

#define MOTOR_LEFT_PORT 1
#define MOTOR_RIGHT_PORT 10

#define SHUTTER_PORT 11
#define COUNTER_PORT 12

#define ULTRASONIC_INPUT_PORT 1     /* on the sensor, this would be its output port */
#define ULTRASONIC_OUTPUT_PORT 7    /* on the sensor, this would be the input port */

#define PD_MODE_PORT 10




#endif /* ROBOT_CONFIG_H */
