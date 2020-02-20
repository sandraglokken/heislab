#include "hardware.h"
#include "queue_system.h"
#include <stdlib.h>
#include "queue_system.h"
#include "movement.h"


void erase_floor_from_orders_switch_of_light(int floor, Orders orders){
  orders.array_orders_up[floor]=0;
  orders.array_orders_down[floor]=0;
  if(orders.array_order_queue[0]==floor){
    left_shift_elements_in_queue(orders);
  }
  hardware_command_order_light(floor,HARDWARE_ORDER_UP,0);
  hardware_command_order_light(floor,HARDWARE_ORDER_DOWN,0);
  hardware_command_order_light(floor,HARDWARE_ORDER_INSIDE,0);
}

void get_pushed_button_switch_on_lights(Order order){
  for(int f=0; f<HARDWARE_NUMBER_OF_FLOORS;f++){
    if(hardware_read_order(f,HARDWARE_ORDER_INSIDE)){
      add_floor_to_queue(f,order);
      hardware_command_order_light(f,HARDWARE_ORDER_INSIDE,1);
    }
    if(hardware_read_order(f,HARDWARE_ORDER_UP)){
      order.array_orders_up[f]=1;
      hardware_command_order_light(f,HARDWARE_ORDER_UP,1);
    }
    if(hardware_read_order(f,HARDWARE_ORDER_DOWN)){
      order.array_orders_down[f]=1;
      hardware_command_order_light(f,HARDWARE_ORDER_DOWN,1);
    }
  }
}

void add_floor_to_queue(int floor, Orders orders){
  for (int f=0; f<HARDWARE_NUMBER_OF_FLOORS;f++){
    if((orders.array_order_queue==-1)||(orders.array_order_queue==floor)){
      orders.array_order_queue[f]=floor;
      return;
    }
  }
}

void left_shift_elements_in_queue(Orders orders){
  int copy_of_queue[HARDWARE_NUMBER_OF_FLOORS];
  for (int f=1; f<(HARDWARE_NUMBER_OF_FLOORS+1);f++){
    copy_of_queue[f-1]=orders.array_order_queue[f-1];
    orders.array_order_queue[f-1]=copy_of_queue[f];
  }
  orders.array_order_queue[(HARDWARE_NUMBER_OF_FLOORS-1)]=-1;
}



void set_next_floor(Orders orders, Elevator elevator){
  elevator.next_floor=orders.array_order_queue[0];
  //IKKW FERDIG

}

void delete_orders(Orders orders){
  for(int i=0; i<HARDWARE_NUMBER_OF_FLOORS;i++){
    orders.array_orders_up[i]=0;
    order.array_orders_down[i]=0;
    order.array_orders_queue[i]=-1;
  }
}
