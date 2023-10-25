

#include "config.h"
#include "pd.h"
#include "move.h"



void robot_main(void)
{
    int expose_time_ms = 3;


    int state = STATE_FIND_RED;
    do {
        int pd_sum = pd_read(expose_time_ms);
        int pd_max_idx = pd_find_max();
        int pd_max_val = g_PD[pd_max_idx];
        pd_move(pd_sum, pd_max_idx, 5000, NEVER_STOP);


        /* beacon is hit */
        if (0 == GetDigitalInput(LIMIT_SWITCH_PORT))
        {
            move(0); /* halt */
            break;
        }
    } while (STATE_FIND_RED == state);



    state = STATE_TURN_OFF_RED;
    /* keep hitting the beacon until it turns off */
    do {
        int pd_sum;
        /* TODO: swing arm up */
        /* TODO: swing arm down, hard */

        /* check if red is still on */
        pd_sum = pd_read(expose_time_ms);
        if (pd_sum < AMBIENT_LEVEL)
        {
            /* TODO: test this */
            /* move about 1 ft back */
            move(-SLOW_SPEED);
            Wait(200);
            move(0);        /* halt */

            /* TODO: swing arm up */
            break;
        }
    } while (STATE_TURN_OFF_RED == state);



    /* TODO: test this */
    state = STATE_FIND_GREEN;
    do {
        int pd_sum = pd_read(expose_time_ms);
        int pd_max_idx = pd_find_max();
        int pd_max_val = g_PD[pd_max_idx];
        pd_move(pd_max_val, pd_max_idx, 2000, NEVER_STOP);


        if (0 == GetDigitalInput(LIMIT_SWITCH_PORT))
        {
            move(0); /* halt */
            break;
        }
    } while (STATE_FIND_GREEN == state);



    state = STATE_CAPTURE_GREEN;
    do {
        /* TODO: capture green */
    } while (STATE_CAPTURE_GREEN == state);



    /* TODO: test this */
    state = STATE_GO_HOME;
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


