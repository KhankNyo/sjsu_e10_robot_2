
#include "UserInclude.h"
#include "cpd.h"
#include "cmove.h"
#include "cutils.h"



int g_PD[8] = { 0 };

/* TODO: check this with the Goto Beacon code and test this */
static int expose_and_read(void)
{
    int intensity;
    SetDigitalOutput(SHUTTER_PORT, 1);  /* close it */
    Wait(5);                            /* again settling time? */
    SetDigitalOutput(SHUTTER_PORT, 0);

    intensity = GetAnalogInput(1);  /* get the IR intensity */
    return intensity;
}




int pd_read(int expose_time_ms)
{
    unsigned i;
    int PD_sum = 0;
    SetDigitalOutput(SHUTTER_PORT, 1);  /* close it */
    SetDigitalOutput(COUNTER_PORT, 1);  /* counter reset */
    SetDigitalOutput(COUNTER_PORT, 0);  /* counter count */

    Wait(5);                            /* settling time? */

    SetDigitalOutput(SHUTTER_PORT, 0);  /* open it */
    Wait(expose_time_ms);               /* expose shutter port to smth idk */

    g_PD[0] = GetAnalogInput(1);        /* read intensity reading */
    for (i = 1; i < STATIC_ARRAY_SIZE(g_PD); i++)
    {
        g_PD[i] = expose_and_read();
        PD_sum += g_PD[i];
    }
    return PD_sum;
}





int pd_find_max(void)
{
    unsigned i;
    int largest = 0;
    for (i = 0; i < STATIC_ARRAY_SIZE(g_PD); i++)
    {
        if (g_PD[i] > g_PD[largest])
            largest = i;
    }
    return largest;
}




void pd_move(int PD_sum, int PD_max_idx, int beacon_slow, int beacon_stop)
{
    int error = PD_MIDDLE - PD_max_idx;
    int steer = error * STEER_SENSITIVITY;
    int speed = FORWARD_SPEED;

    /* start searching for the beacon */
    if (PD_sum < AMBIENT_LEVEL)
    {
        /* spinning on a dime */
        speed = 0;
        steer = -SPIN_SPEED;
    }
    /* slow down */
    else if (PD_sum > beacon_slow)
    {
        speed = SLOW_SPEED;
    }
    /* stop all speeds */
    else if (PD_sum > beacon_stop)
    {
        speed = 0;
        steer = 0;
    }

    turn(speed, steer);
}

