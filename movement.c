
#include "hardware.h"
#include <stdlib.h>
#include "queue_system.h"
#include "movement.h"

int check_movement_conditions(Elevator elevator){
	if (harware_read_stop_signal() || elevator.door){
		return 0;
	}
	return 1;
}


int get_next_floor(Orders orders){
	if (orders.next_floor< 0 || orders.next_floor>= HARDWARE_NUMBER_OF_FLOORS){
		hardware_command_movement(HARDWARE_MOVEMENT_STOP);
		return HARDWARE_NUMBER_OF_FLOORS;
	}
	return orders.next_floor;
}



void set_door(Elevator elevator,int door_open){
	elevator.door =door_open;
	hardware_command_door_open(door_open);
	if (door_open==1){
		start_timer(elevator);
	}
}

void set_direction_bit(Elevator elevator, int direction){
	elevator.direction_bit=direction;
}

void set_current_floor(Elevator elevator){
	for (int f;f<HARDWARE_NUMBER_OF_FLOORS;f++){
		if(hardware_read_floor_sensor(f)){
			elevator.current_floor=f;
		}
	}
}


void set_movement(Elevator elevator, Orders orders){
	if (check_movement_conditions(elevator)){
		int diff_floors, next_floor;
		next_floor = get_next_floor(orders);
		diff_floors = elevator.current_floor - next_floor;
		if (!hardware_read_floor_sensor(next_floor)){
			if (diff_floors< 0){
				hardware_command_movement(HARDWARE_MOVEMENT_UP);
				set_direction_bit(elevator,2);
				if(orders.array_orders_up[elevator.current_floor+1]){
					elevtor.next_floor=(elevator.current_floor+1);
				}
			}
			if (diff_floors > 0){
				hardware_command_movement(HARDWARE_MOVEMENT_DOWN);
				set_direction_bit(elevator,1);
				if(orders.array_orders_down[elevator.current_floor-1]){
					elevtor.next_floor=(elevator.current_floor-1);
				}
			}
		}
		if(hardware_read_floor_sensor(next_floor)){
			stop_at_floor(elevator, elevator.current_floor, orders);
		}
	}
	set_current_floor(elevtor);
}

void stop_at_floor(Elevator elevator, int floor, Orders orders){
	hardware_command_movement(HARDWARE_MOVEMENT_STOP);
	set_direction_bit(elevator,0);
	erase_floor_from_orders_switch_of_light(floor, orders);
	set_door(elevtor,1);
	while_waiting_3_sec(orders);
	while(hardware_read_obstruction_signal()||hardware_read_stop_signal()){
		while_waiting_3_sec(orders);
	}
	set_door(elevator,0);
	get_next_floor(orders);
}
