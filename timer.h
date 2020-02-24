/**
 *@file
 *
 *@brief Makes a timer for the door
 *
*/
#include <timer.h>
#include <stdlib.h>
#include "movement.h"

/**
 *
 *@brief Checks the current time stamp
 *
 *@return Returns a start time
*/
clock_t start_timer();

/**
 *
 *@brief Calculates the difference between now and @p start_time
 *
 *@param start_time the start time from @c start_timer
 *
 *@return Returns the time difference in sec
*/
int time_difference(clock_t start_time);
}

/**
 *
 *@brief Waits for 3 seconds while still taking orders and checking the stop button
 *
 *@param orders The orders struct to access the order arrays
 *
*/
void while_waiting_3_sec(Orders* orders);
