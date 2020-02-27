#include "hardware.h"
#include "queue_system.h"
#include <stdlib.h>
#include "queue_system.h"
#include "movement.h"


void erase_floor_from_orders(int floor, Orders* orders){
  if(floor!=-1){
    orders->array_orders_up[floor]=0;
    orders->array_orders_down[floor]=0;
    orders->array_orders_inside[floor]=0;
    left_shift_elements_in_queue(orders);
  }
}

void add_floor_to_queue(int floor, Orders* orders){
  for (int f=0; f<HARDWARE_NUMBER_OF_FLOORS;f++){
    if((orders->array_order_queue[f]==-1)||(orders->array_order_queue[f]==floor)){
      orders->array_order_queue[f]=floor;
      return;
    }
  }
}

void left_shift_elements_in_queue(Orders* orders){
  int copy_of_queue[HARDWARE_NUMBER_OF_FLOORS];
  for (int f=1; f<(HARDWARE_NUMBER_OF_FLOORS+1);f++){
    copy_of_queue[f-1]=orders->array_order_queue[f-1];
  }
  for(int f=1;f<HARDWARE_NUMBER_OF_FLOORS;f++){
    orders->array_order_queue[f-1]=copy_of_queue[f];
  }
  orders->next_floor=orders->array_order_queue[0];
  orders->array_order_queue[(HARDWARE_NUMBER_OF_FLOORS-1)]=-1;
}

void get_pushed_button_switch_on_lights(Orders* orders){
  for(int f=0; f<HARDWARE_NUMBER_OF_FLOORS;f++){
    if(hardware_read_order(f,HARDWARE_ORDER_INSIDE)){
      orders->array_orders_inside[f]=1;
      add_floor_to_queue(f,orders);
      hardware_command_order_light(f,HARDWARE_ORDER_INSIDE,1);
    }
    if(hardware_read_order(f,HARDWARE_ORDER_UP)){
      orders->array_orders_up[f]=1;
      hardware_command_order_light(f,HARDWARE_ORDER_UP,1);
      add_floor_to_queue(f,orders);
    }
    if(hardware_read_order(f,HARDWARE_ORDER_DOWN)){
      orders->array_orders_down[f]=1;
      hardware_command_order_light(f,HARDWARE_ORDER_DOWN,1);
      add_floor_to_queue(f,orders);
    }
  }
}

void set_next_floor(int next_floor, Orders* orders){
  orders->next_floor=next_floor;
}

void move_first_in_line(Orders* orders, int floor){
  int copy_of_queue[HARDWARE_NUMBER_OF_FLOORS];
  for (int f=0; f<(HARDWARE_NUMBER_OF_FLOORS+1);f++){
    copy_of_queue[f]=orders->array_order_queue[f];
  }
  int index;
  for (int f=0; f<HARDWARE_NUMBER_OF_FLOORS;f++){
    if(orders->array_order_queue[f]==floor){
      index=f;
      while(index!=0){
        index--;
        orders->array_order_queue[index]=floor;
        orders->array_order_queue[(index+1)]=copy_of_queue[index];
      }
    }
  }
}

void delete_orders(Orders* orders){
  for(int i=0; i<HARDWARE_NUMBER_OF_FLOORS;i++){
    orders->array_orders_up[i]=0;
    orders->array_orders_down[i]=0;
    orders->array_orders_inside[i]=0;
    orders->array_order_queue[i]=-1;
    orders->next_floor=-1;
  }
}

void initialize_orders(Orders* orders){
  for (int i=0;i<HARDWARE_NUMBER_OF_FLOORS;i++){
    orders->array_order_queue[i]=-1;
  }
  orders->next_floor=-1;

}