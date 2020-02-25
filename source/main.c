#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <string.h>
#include "hardware.h"
#include "queue_system.h"
#include "movement.h"



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
    clear_all_order_lights();
    initialize_orders(&orders);
    initialize_elevator(&elevator);

    while(1){
        check_stop_signal(&orders,&elevator);
        hardware_command_stop_light(0);
        set_floor_indicators();
        get_pushed_button_switch_on_lights(&orders);
        sort_orders(&orders,&elevator);
        set_movement(&elevator, &orders);
        set_current_floor(&elevator);
    }
}
