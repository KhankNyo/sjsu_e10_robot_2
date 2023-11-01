

#include "UserInclude.h"
#include "cpd.h"
#include "cmove.h"



static int s_expose_time_ms = 3;

static void find_red(int state)
{
    /* TODO: check the move fn because in cmove.c, cpd.c
     *  Robot went in a straight line instead of spinning with the faulty controller
     */
    do {
        int pd_sum = pd_read(s_expose_time_ms);
        int pd_max_idx = pd_find_max();
        pd_move(pd_sum, pd_max_idx, 5000, NEVER_STOP);


        /* beacon is hit */
        if (0 == GetDigitalInput(LIMIT_SWITCH_PORT))
        {
            move(0); /* halt */
            break;
        }
    } while (STATE_FIND_RED == state);
}


static void turn_off_red(int state, int wait_time_ms)
{
#define ARM_UP 0
#define ARM_DOWN 127
    /* make sure arm is up */
    SetServo(ARM_SERVO_PORT, ARM_UP);
    Wait(wait_time_ms);

    do {
        /* try to turn off the red beacon */
        SetServo(ARM_SERVO_PORT, ARM_DOWN); 
        Wait(wait_time_ms);

        /* move arm up */
        SetServo(ARM_SERVO_PORT, ARM_UP); 
        Wait(wait_time_ms);

        /* is the red beacon off? */
        if (pd_read(s_expose_time_ms) < AMBIENT_LEVEL)
        {
            /* move about 1 ft back */
            move(-SLOW_SPEED);
            Wait(200);

            /* halt */
            move(0);
            break;
        }
    } while (STATE_TURN_OFF_RED == state);
#undef ARM_UP
#undef ARM_DOWN
}


static void bringing_home_the_beacon(void) {
    /* TODO: possible merge conflict with the code in EasyC */
    do {
        // bring arm max down (capture beacon)
        SetServo(1,127);
    } while (STATE_CAPTURE_GREEN == state);
}

static void find_green(int state)
{

    do {
        int pd_sum = pd_read(s_expose_time_ms);
        int pd_max_idx = pd_find_max();
        pd_move(pd_sum, pd_max_idx, 2000, NEVER_STOP);


        if (0 == GetDigitalInput(LIMIT_SWITCH_PORT))
        {
            move(0); /* halt */
            break;
        }
    } while (STATE_FIND_GREEN == state);
}


static void capture_green(int state)
{
    do {
        /* TODO: capture green */
    } while (STATE_CAPTURE_GREEN == state);
}


static void go_home(int state)
{

    StartUltrasonic(ULTRASONIC_INPUT_PORT, ULTRASONIC_OUTPUT_PORT); /* init ultrasonic sensor */
    move(-FORWARD_SPEED);                                           /* backing up */
    do {
        /* in inches */
        int dist = GetUltrasonic(ULTRASONIC_INPUT_PORT, ULTRASONIC_OUTPUT_PORT);

        /* if wall in sight, rotate 90 degrees to the right */
        /* then back up and repeat */
        if (dist < MIN_DIST_TO_WALL)
        {
            /* TODO: test this, make sure it's close to a 90 degrees rotation */
            move(0);                    /* halt */
            turn(0, FAST_SPIN_SPEED);   /* turn */
            Wait(100);                  /* turn for some time */

            /* start moving again, might need a halt before to stabilize the robot */
            move(-FORWARD_SPEED);       
        }
    } while (STATE_GO_HOME == state);
}







void robot_main(void)
{
    s_expose_time_ms = 3;
    int state = STATE_FIND_RED;
    find_red(state);


    state = STATE_TURN_OFF_RED;
    turn_off_red(state, 1000);
   
    #if 0

    /* TODO: test this */
    state = STATE_FIND_GREEN;
    find_green(state);


    state = STATE_CAPTURE_GREEN;
    capture_green(state);


    /* TODO: test this */
    state = STATE_GO_HOME;
    go_home(state);

    #endif 
}


