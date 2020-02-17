/**
 *@file
 *
 *@brief Makes the queue system for the elevator
 *
*/ 


#include "hardware.h"
#include <stdlib.h>

/**
 * @brief Order	Struct used to set orders and priority
*/

typedef struct{
	int current_floor;		/**< The current floor of the elevator*/
	int array_orders_up[4];		/**< An array for orders up with four elements for the four floors, each containt 0 or 1 for no orders/orders.*/
	int array_orders_down[4];	/**< An array for orders down with four elements for the four floors, each containt 0 or 1 for no orders/orders.*/
	int array_orders_inside[4];	/**< An array for orders from the elevator panel with four elements for the four floors, each containt 0 or 1 for no orders/orders.*/
	int next_floor;			/**< The next floor the elevator will stop in*/
}Orders;

/**
 * @brief Erase the floor from orders list when the elevator stops in ordered floor
 *
 * @param floor	The floor that will be erased from @p orders
 * @param orders deletes @p floor from all orders-arrays
*/
void erase_floor_from_orders(int floor, Orders orders);

/**
 *@brief Finds the next floor that the elevator will stop
 *
 *@param orders	All the orders of the elevator
 *
 *@param elevator_direction The direction of the elevator, 0 for standstill, 1 for up and 2 for down
 *
*/
void set_next_floor(Orders orders, Elevator elevator_direction);


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



