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
 *@brief Enum to describe the movement of the elevator
 */
typedef enum{
	UP,
	DOWN,
	IDLE,
} Direction;

/**
 * @brief Elevator Struct used to set the current state of the elevator
*/
typedef struct{
	int door;		/**< 0 if the door is closed, 1 if the door is open*/
	int obstruction;	/**< 0 if the obstructin stick is not active, 1 if it is active */
	int current_floor;	/**< The current floor of the elevator, 0,1,2 or 3*/
	Direction direction;	/**< The direction of the elevator*/
	int above; 			/**< If the elevator is above or under the current_floor, 1 for above, 0 for under*/
}Elevator;



/**
 *@brief Checks all conditions for the elevator to move
 *
 *@param elevator To get the status of the door (open=1/closed=0)
 *
 *@param orders To check if there is a next floor order, -1 if not
 *
 *@return Returns 1 if all conditions are met, 0 if not
 *
*/
int check_movement_conditions(Elevator* elevator, Orders* orders);


/**
 * @brief gets the next floor from @p orders
 *
 * @param orders To access the next floor to go to
 *
 * @return Returns the next floor the elevator will move to
 *
 * @warning Returns -1 if there is no orders
*/
int get_next_floor(Orders* orders);

/**
 *
 *@brief turns the order lights for the @p floor off
 *
 *@param floor The floor the order lights will be turned of
 *
*/
void turn_off_order_lights(int floor);

/**
 * @brief Opens the door and closes it when all conditions for closing are met
 *
 * @param elevator To set the value of the door in the Elevator struct
 *
 * @param door_open Set to 1 for opening the door, 0 to close.
 *
 * @param orders Used to keep taking orders while waiting.
 *
*/
void set_door(Elevator* elevator, int door_open, Orders* orders);

/**
* @brief Sets the direction of the elevator to @p direction
*
* @param direction the direction the elevator is moving
*
* @param elevator to access the direction bit
*
*/

void set_direction(Elevator* elevator, Direction direction);

/**
 * @brief Updates the current floor of the elevator
 *
 * @param elevator The elevator struct to access the current_floor variable
 *
 */

void set_current_floor(Elevator* elevator);


/**
 *
 *@brief Checks if the @p next_floor is over or under the current floor, and sets the elevator in movement
 *
 *@parma elevator to access the current floor of the elevator
 *
 *@param next_floor the next floor in the queue
 *
*/

void set_movement_direction(Elevator* elevator, int next_floor);

/**
 * @brief Sets the elevator in the correct movement
 *
 * @param elevator Elevator struct with the current state
 *
 * @param orders The order of the elevator with the next floor to go to
 *
*/
void set_movement(Elevator* elevator, Orders* orders);



/**
 * @brief Stops the elevator in a floor, opens door for 3 secs, checks conditions for closing door before closing
 *
 * @param elevator Elevator struct with the current state
 *
 * @param orders Used to update the Orders struct
 *
*/
void stop_at_floor(Elevator* elevator, Orders* orders);

/**
 * @brief Sorts the queue of orders in the prioritized order
 *
 * @param orders Used to change the order in order queue
 *
 * @param elevator Used to get the direction and current floor from the elevator struct
 *
*/

void sort_orders(Orders* orders, Elevator* elevator);

/**
 * @brief Sets the floor indicators if the floor sensor is high
 *
 */

void set_floor_indicators();

/**
 *
 *@brief Sets the elevator in its initial state
 *
 *@param elevator Elevator struct to set the initial values
 *
*/

void initialize_elevator(Elevator* elevator);

/**
 * @brief turns off all order lights for all floors
 * 
 */
void clear_all_order_lights();

/**
 * @brief Checks if the next floor is the same as current floor in elevator after stopping between floors
 * 
 * @param orders checks the next order
 * 
 * @param elevator to access the current floor
 *
 */
void after_stopping_between_floors(Orders* orders, Elevator* elevator);

/**
 *
 *@brief Checks if the stop signal, if it is high the elevator is set to stop-state
 *
 *@param orders To access and delete all the orders and order queue
 *
*/
void check_stop_signal(Orders* orders,Elevator* elevator);

#endif
