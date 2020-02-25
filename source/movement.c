
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

void turn_off_order_lights(int floor){
	hardware_command_order_light(floor,HARDWARE_ORDER_UP,0);
  hardware_command_order_light(floor,HARDWARE_ORDER_DOWN,0);
  hardware_command_order_light(floor,HARDWARE_ORDER_INSIDE,0);
}

void set_door(Elevator* elevator,int door_open, Orders* orders){
	elevator->door =door_open;
	hardware_command_door_open(door_open);
	if (door_open==1){
		while_waiting_3_sec( orders);
	}
}

void set_direction(Elevator* elevator, Direction direction){
	elevator->direction=direction;
}

void set_current_floor(Elevator* elevator){
	for (int f;f<HARDWARE_NUMBER_OF_FLOORS;f++){
		if(hardware_read_floor_sensor(f)){
			elevator->current_floor=f;
		}
	}
}

void set_movement_direction(Elevator* elevator, int next_floor){
	int floor_difference = elevator->current_floor - next_floor;
	if (!hardware_read_floor_sensor(next_floor)){
		if (floor_difference< 0){
			hardware_command_movement( HARDWARE_MOVEMENT_UP );
			set_direction( elevator, UP);
		}
		if (floor_difference > 0){
			hardware_command_movement( HARDWARE_MOVEMENT_DOWN );
			set_direction( elevator, DOWN);
		}
	}
}

void set_movement(Elevator* elevator, Orders* orders){
	int next_floor = orders->next_floor;
	set_current_floor(elevator);
	if (check_movement_conditions(elevator,orders)){
		set_movement_direction(elevator, next_floor);
	}
	if(hardware_read_floor_sensor(next_floor)){
		set_current_floor(elevator);
		stop_at_floor( elevator, orders);
	}
}

void stop_at_floor(Elevator* elevator, Orders* orders){
	hardware_command_movement(HARDWARE_MOVEMENT_STOP);
	turn_off_order_lights(orders->next_floor);
	erase_floor_from_orders(elevator->current_floor, orders);
	set_direction( elevator,IDLE);
	set_floor_indicators();
	set_door( elevator,1, orders);
	set_door( elevator,0, orders);
}

void sort_orders(Orders* orders, Elevator* elevator){
  if(elevator->direction==UP){
    for(int f=orders->next_floor;f>elevator->current_floor;f--){
      if(orders->array_orders_up[f]==1 || orders->array_orders_inside[f]==1){
        move_first_in_line(orders,f);
      }
    }
  }
  if(elevator->direction==DOWN){
	for(int f=orders->next_floor;f<elevator->current_floor;f++){
      if(orders->array_orders_down[f]==1|| orders->array_orders_inside[f]==1){
        move_first_in_line(orders,f);
      }
    }
  }
  set_next_floor(orders->array_order_queue[0],orders);
}

void set_floor_indicators(){
	for(int f=0;f<HARDWARE_NUMBER_OF_FLOORS;f++){
		if (hardware_read_floor_sensor(f)){
			hardware_command_floor_indicator_on(f);
        }
    }
}

void initialize_elevator(Elevator* elevator){
	for(int f=0;f<HARDWARE_NUMBER_OF_FLOORS;f++){
      int i=0;
      if(hardware_read_floor_sensor(f)){
          i++;
      }
      if(i==0){
        hardware_command_movement(HARDWARE_MOVEMENT_UP);
      }
      while(i==0){
        for(int f=0;f<HARDWARE_NUMBER_OF_FLOORS;f++){
          if(hardware_read_floor_sensor(f)){
              i++;
          }
        }
      }
    }
    hardware_command_movement(HARDWARE_MOVEMENT_STOP);
    for(int f=0;f<HARDWARE_NUMBER_OF_FLOORS;f++){
      /*hardware_command_order_light(f,HARDWARE_ORDER_DOWN,0);
      hardware_command_order_light(f,HARDWARE_ORDER_UP,0);
      hardware_command_order_light(f,HARDWARE_ORDER_INSIDE,0);*/
      if(hardware_read_floor_sensor(f)){
        elevator->current_floor=f;
      }
    }
}
void clear_all_order_lights(){
    HardwareOrder order_types[3] = {
        HARDWARE_ORDER_UP,
        HARDWARE_ORDER_INSIDE,
        HARDWARE_ORDER_DOWN
    };

    for(int f = 0; f < HARDWARE_NUMBER_OF_FLOORS; f++){
        for(int i = 0; i < 3; i++){
            HardwareOrder type = order_types[i];
            hardware_command_order_light(f, type, 0);
        }
    }
}
void after_stopping_between_floors(Orders* orders, Elevator* elevator){
	if(orders->array_order_queue[0]==elevator->current_floor){
		if(elevator->direction==UP){
			elevator->current_floor=(elevator->current_floor+1);
		}

		if(elevator->direction==DOWN){
			elevator->current_floor=(elevator->current_floor-1);
		}
	}
}

void check_stop_signal(Orders* orders, Elevator* elevator){
	if(hardware_read_stop_signal()){
		while(hardware_read_stop_signal()){
				hardware_command_movement(HARDWARE_MOVEMENT_STOP);
				hardware_command_stop_light(1);
				clear_all_order_lights();
				delete_orders(orders);
				if(elevator->direction==IDLE){
					set_door(elevator,1,orders);
				}
		}
		hardware_command_stop_light(0);
		set_door(elevator,0,orders);
		while(orders->array_order_queue[0]==-1){
			get_pushed_button_switch_on_lights(orders);
		}
		after_stopping_between_floors(orders,elevator);
	}	
}
