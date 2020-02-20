#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include "hardware.h"
#include "queue_system.h"
#include "movement.h"

static void clear_all_order_lights(){
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

static void sigint_handler(int sig){
    (void)(sig);
    printf("Terminating elevator\n");
    hardware_command_movement(HARDWARE_MOVEMENT_STOP);
    exit(0);
}

int main(){
    int error = hardware_init();
    if(error != 0){
        fprintf(stderr, "Unable to initialize hardware\n");
        exit(1);
    }

    signal(SIGINT, sigint_handler);

    printf("=== Example Program ===\n");
    printf("Press the stop button on the elevator panel to exit\n");
    Elevator* elevator;
    Orders* orders;
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
      hardware_command_movement(HARDWARE_MOVEMENT_STOP);
      for(int f=0;f<HARDWARE_NUMBER_OF_FLOORS;f++){
        if(hardware_read_floor_sensor(f)){
          elevator->current_floor=f;
        }
      }
      elevator->door=0;
      elevator->obstructin=0;
      elevtor->direction_bit=0;



    while(1){
        while(hardware_read_stop_signal()){
            hardware_command_movement(HARDWARE_MOVEMENT_STOP);
            hardware_command_stop_light(1);
            for(int f=0;f<HARDWARE_NUMBER_OF_FLOORS;f++){
              if(hardware_read_floor_sensor(f)){
                set_door(elevator,1);
              }
            }
          hardware_command_stop_light(0);
        }
        if(elevator->next_floor==-1){
          hardware_command_movement(HARDWARE_MOVEMENT_STOP);
        }
        set_movement(elevator, orders);
        get_pushed_button_switch_on_lights(orders);
        //set_current_floor(elevtor);
}
