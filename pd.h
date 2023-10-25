#ifndef ROBOT_PHOTO_DETECTOR_H
#define ROBOT_PHOTO_DETECTOR_H


extern int g_PD[8];


/* 
 * reads PD sensor, and then
 * returns the sum of all pd's, including PD0
 */
int pd_read(int expose_time_ms);

/* 
 * find the PD with the greatest reading, 
 * returns its index 
 */
int pd_find_max(void);

/*
 * PD_sum: sum of all PD's, including PD0
 * PD_max_idx: the index of the PD that contains the max reading
 * beacon_slow: intensity threshold to slow down the robot (beacon is near)
 * beacon_stop: intensity threshold to stop the robot (beacon is close/within reach)
 */
void pd_move(int PD_sum, int PD_max_idx, int beacon_slow, int beacon_stop);



#endif /* ROBOT_PHOTO_DETECTOR_H */

