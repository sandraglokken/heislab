#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <string.h>
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

    printf("=== Elevator Program ===\n");
   
    Elevator elevator;
    memset(&elevator, 0, sizeof(Elevator));
    Orders orders;
    memset(&orders, 0, sizeof(Orders));
    for (int i=0;i<HARDWARE_NUMBER_OF_FLOORS;i++){
      orders.array_order_queue[i]=-1;
    }
    orders.next_floor=-1;


    initialize(&elevator);

    while(1){
        while(hardware_read_stop_signal()){
            hardware_command_movement(HARDWARE_MOVEMENT_STOP);
            hardware_command_stop_light(1);
            clear_all_order_lights();
            delete_orders(&orders);
        }
        hardware_command_stop_light(0);
        set_floor_indicators();
        get_pushed_button_switch_on_lights(&orders);
        sort_orders(&orders,&elevator);
        set_movement(&elevator, &orders);
        set_current_floor(&elevator);
    }
}
