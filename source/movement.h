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
 *@return Returns 1 if all conditions are met, 0 if not
*/
int check_movement_conditions();


/**
 * @brief gets the next floor from @p orders
 *
 * @param orders struct from queue_system.h 
 * 
 * @return Returns the next floor the elevator will move to
*/
int get_next_floor(Orders orders);

/**
 * @brief Sets the elevator in movement using @c hardware_command_movement and @c get_next_floor
 * 
 * @param elevator Elevator struct with the current state
*/
void set_movement(Elevator elevator);

/**
 * @brief Changes the value of Elevator.door
 *
*/

void set_door();

/**
* @brief Sets Elevator.direction_bit depending on wether the elevator is moving up, down or standing still.
*/

void set_direction_bit();

#endif



