#ifndef ROBOT_MOVE_H
#define ROBOT_MOVE_H


/* move the robot in one direction according to the speed given */
void move(int speed);

/* 
    Steer: <  0 means turn right,
           >  0 means turn left,
           == 0 means going straight, no steering
    speed: determines the speed at which to robot steers
*/
void turn(int speed, int steer);


#endif /* ROBOT_MOVE_H */
