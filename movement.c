
#include "hardware.h"
#include <stdlib.h>
#include "queue_system.h"
#include "movement.h"

int check_movement_conditions(Elevator* elevator, Orders* orders){
	if (hardware_read_stop_signal() || elevator->door || (orders->next_floor==-1)){
		return 0;
	}
	return 1;
}

int get_next_floor(Orders* orders){
	if (orders->next_floor< 0 || orders->next_floor>= HARDWARE_NUMBER_OF_FLOORS){
		hardware_command_movement(HARDWARE_MOVEMENT_STOP);
		return -1;
	}
	return orders->next_floor;
}

void set_door(Elevator* elevator,int door_open, Orders* orders){
	elevator->door =door_open;
	hardware_command_door_open(door_open);
	if (door_open==1){
		while_waiting_3_sec( orders);
	}
}

void set_direction_bit(Elevator* elevator, int direction){
	elevator->direction_bit=direction;
}

void set_current_floor(Elevator* elevator){
	for (int f;f<HARDWARE_NUMBER_OF_FLOORS;f++){
		if(hardware_read_floor_sensor(f)){
			elevator->current_floor=f;
		}
	}
}

void set_movement(Elevator* elevator, Orders* orders){
	int next_floor = orders->next_floor;
	set_current_floor(elevator);
	if (check_movement_conditions(elevator,orders)){
		int diff_floors;
		diff_floors = elevator->current_floor - next_floor;
		if (!hardware_read_floor_sensor(next_floor)){
			if (diff_floors< 0){
				hardware_command_movement(HARDWARE_MOVEMENT_UP);
				set_direction_bit( elevator,2);
			}
			if (diff_floors > 0){
				hardware_command_movement(HARDWARE_MOVEMENT_DOWN);
				set_direction_bit( elevator,1);				
			}
		}
		if(hardware_read_floor_sensor(next_floor)){
			hardware_command_movement(HARDWARE_MOVEMENT_STOP);
			//hardware_command_floor_indicator_on(elevator->current_floor);
			stop_at_floor( elevator, orders);
		}
	}
	else{
		hardware_command_movement(HARDWARE_MOVEMENT_STOP);
	}
}

void stop_at_floor(Elevator* elevator, Orders* orders){
	erase_floor_from_orders_switch_of_light(elevator->current_floor, orders);
	set_direction_bit( elevator,0);
	set_door( elevator,1, orders);
	if(hardware_read_obstruction_signal()||hardware_read_stop_signal()){
		while(hardware_read_stop_signal()){
			set_door(elevator,1,orders);
		}
		hardware_command_stop_light(0);
		while(hardware_read_obstruction_signal()){
			set_door(elevator,1,orders);
		}
	}
	set_door( elevator,0, orders);
}

void sort_orders(Orders* orders, Elevator* elevator){
  if(elevator->direction_bit==2){
    for(int f=orders->next_floor;f>elevator->current_floor;f--){
      if(orders->array_orders_up[f]==1){
        move_first_in_line(orders,f);
      }
    }
  }
  if(elevator->direction_bit==1){
    for(int f=orders->next_floor;f<elevator->current_floor;f++){
      if(orders->array_orders_down[f]==1){
        move_first_in_line(orders,f);
      }
    }
  }
  set_next_floor(orders->array_order_queue[0],orders);
}

