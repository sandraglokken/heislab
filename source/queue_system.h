/**
 *@file
 *
 *@brief Makes the queue system for the elevator
 *
*/

#ifndef QUEUE_SYSTEM_H
#define QUEUE_SYSTEM_H


#include "hardware.h"
#include <stdlib.h>

/**
 * @brief Order	Struct used to set orders and priority
*/

typedef struct{
	int array_order_queue[HARDWARE_NUMBER_OF_FLOORS]; /**<An array for order the sequence inside the elevator, no order=-1 */
	int array_orders_up[HARDWARE_NUMBER_OF_FLOORS];		/**< An array for orders up with four elements for the four floors, each containt 0 or 1 for no orders/orders.*/
	int array_orders_down[HARDWARE_NUMBER_OF_FLOORS];	/**< An array for orders down with four elements for the four floors, each containt 0 or 1 for no orders/orders.*/
	int array_orders_inside[HARDWARE_NUMBER_OF_FLOORS]; /**<An array for orders inside the elevator with four elements for the four floors, each containt 0 or 1 for no orders/orders.*/
	int next_floor;			/**< The next floor the elevator will stop in, =-1 if no orders*/
}Orders;

/**
 * @brief Erase the floor from orders list when the elevator stops in ordered floor
 *
 * @param floor	The floor that will be erased from @p orders
 *
 * @param orders deletes @p floor from all order-arrays
*/
void erase_floor_from_orders(int floor, Orders* orders);


/**
 *@brief Adds a floor to the order queue
 *
 *@param floor the floor being requested
 *
 *@param orders Order struct for acessing the queue array
 *
*/
void add_floor_to_queue(int floor, Orders* orders);


/**
 *@brief Shift the elemtents to the left - same as deleting the first element ant moving all other one step forward
 *
 *@param orders Order struct for acessing the queue array
*/
void left_shift_elements_in_queue(Orders* orders);

/**
 *@brief Registrates the pushed buttons from the elevator panel and the floor panel to the arrays in order, and switch on the order lights
 *
 *@param orders The struct to save all three types of orders
 *
*/
void get_pushed_button_switch_on_lights(Orders* orders);


/**
 *@brief Finds the next floor that the elevator will stop at
 *
 *@param next_floor The floor that will be the next floor
 *
 *@param orders @p next_floor will be saved in the orders.next_floor.
 *
*/
void set_next_floor(int next_floor, Orders* orders);


/**
 * @brief Moves a @p floor first in the queue
 *
 * @param orders To access the queue array
 *
 * @param floor The floor that will be moved first in line
 *
*/
void move_first_in_line(Orders* orders, int floor);



/**
 *@brief Deletes all orders from @p orders
 *
 *@param orders The struct with the orders to delete
 *
*/

void delete_orders(Orders* orders);


/**
 *
 *@brief Sets the order in its initial state
 *
 *@param orders Orders struct to set the initial values
 *
*/
void initialize_orders(Orders* orders);

#endif
