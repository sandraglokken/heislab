/**
 *@file
 *
 *@brief Makes the movement system for the elevator
 *
*/
#ifndef MOVEMENT_H
#define MOVEMENT_H

#include "hardware.h"
#include <stdlib.h>
#include "queue_system.h"
#include "timer.h"


/**
 * @brief Elevator Struct used to set the current state of the elevator
*/
typedef struct{
	int door;		/**< 0 if the door is closed, 1 if the door is open*/
	int obstruction;	/**< 0 if the obstructin stick is not active, 1 if it is active */
	int current_floor;	/**< The current floor of the elevator, 0,1,2 or 3*/
	int direction_bit;	/**< The direction of the elevator, 0 for standstill, 1 for up and 2 for down*/
}Elevator;

/**
 *@brief Checks all conditions for the elevator to move
 *
 *@param elevator To get the status of the door (open/closed)
 *@return Returns 1 if all conditions are met, 0 if not
*/
int check_movement_conditions(Elevator* elevator);


/**
 * @brief gets the next floor from @p orders
 *
 * @param orders struct from queue_system.h
 *
 * @return Returns the next floor the elevator will move to
 *
 * @warning Returns HARDWARE_NUMBER_OF_FLOORS if there is no orders
*/
int get_next_floor(Orders* orders);


/**
 * @brief Changes the value of Elevator.door
 *
 * @param elevator Uses elevator.door to set if the door i closed or open.
 * @param door_open Set to 1 to open the door, 0 to close. Sets the value of elevator.door
*/
void set_door(Elevator* elevator, int door_open);

/**
* @brief Sets Elevator.direction_bit depending on wether the elevator is moving up(2), down(1) or standing still(0).
* @param direction the direction the elevator is moving
* @param elevator Elevator struct to set its direction bit
*/

void set_direction_bit(Elevator* elevator,int direction);

/**
 * @brief Updates the current floor of the elevator
 *
 * @param elevator The elevator struct to update its current floor
 *
 */

void set_current_floor(Elevator* elevator);

/**
 * @brief Sets the elevator in movement using @c hardware_command_movement and @c get_next_floor
 *
 * @param elevator Elevator struct with the current state
 * @param orders The order of the elevator with the next floor to go to
*/
void set_movement(Elevator elevator, Orders orders);



/**
 * @brief Stops the elevator in a floor, opens door for 3 secs, checks conditions for closing door before closing
 *
 * @param elevator Elevator struct with the current state
 *
*/
void stop_at_floor(Elevator elevator);

#endif
