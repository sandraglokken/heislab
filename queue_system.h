/**
 *@file
 *
 *@brief Makes the queue system for the elevator
 *
*/

#ifndef QUEUE_SYSTEM_H
#define QUEUE_SYSTEM_H
#define MAX 50

#include "hardware.h"
#include <stdlib.h>

/**
 * @brief Order	Struct used to set orders and priority
*/

typedef struct{
	int array_order_queue[HARDWARE_NUMBER_OF_FLOORS]={-1,-1,-1,-1}; /**<An array for order the sequence inside the elevator, no order=-1 */
	int array_orders_up[4];		/**< An array for orders up with four elements for the four floors, each containt 0 or 1 for no orders/orders.*/
	int array_orders_down[4];	/**< An array for orders down with four elements for the four floors, each containt 0 or 1 for no orders/orders.*/
	int next_floor=-1;			/**< The next floor the elevator will stop in, =-1 if no orders*/
}Orders;

/**
 * @brief Erase the floor from orders list when the elevator stops in ordered floor
 *
 * @param floor	The floor that will be erased from @p orders
 * @param orders deletes @p floor from all orders-arrays
*/
void erase_floor_from_orders(int floor, Orders orders);


/**
 *@brief Adds a floor to the order queue from inside the elevator
 *
 *@param floor the floor being requested
 *
 *@param orders Order struct for acessing the queue array
 *
*/
void add_floor_to_queue(int floor, Orders orders);


/**
 *@brief Shift the elemtents to the left
 *
 *@param orders Order struct for acessing the queue array
*/
void left_shift_elements_in_queue(Orders orders);

/**
 *@brief Registrates the pushed buttons from the elevator panel and the floor panel to the arrays in order, and switch on the order lights
 *
 *@param order The struct to save all three types of orders
 *
*/
void get_pushed_button_switch_on_lights(Order order);


/**
 *@brief Finds the next floor that the elevator will stop
 *
 *@param orders	All the orders of the elevator
 *
 *@param elevator The direction of the elevator, 0 for standstill, 1 for up and 2 for down
 *
*/
void set_next_floor(Orders orders, Elevator elevator);


/**
 *@brief Deletes all orders from @p orders
 *
 *@param orders The struct with the orders to delete
 *
*/
void delete_orders(Orders orders);

/**
 *@brief Adds a order to @p floor in the right array of orders
 *
 *@param floor The floor that has been requested
 *
 *@param order_type Specifies what type of order it is
 *
 *@param orders @p floor gets added to the right array in this Order struct
 *
*/
void add_order(int floor, HardwareOrder order_type, Orders orders);

#endif
