#ifndef ROBOT_MOVE_H
#define ROBOT_MOVE_H


/* move the robot in one direction according to the speed given */
void move(int speed);

/* @param steer: determines how much to steer to robot, 
 *  0 means spinning on a dime
 *  < 0 means steering to the left
 *  > 0 means steering to the right
 * @param speed: determines how quickly it steers when steer != 0,
 *  when steer == 0, a positive speed means rotate to the right, and vice versa 
 */
void turn(int steer, int speed);


#endif /* ROBOT_MOVE_H */

