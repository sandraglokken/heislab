#include <timer.h>
#include <stdlib.h>
#include "movement.h"
#include "timer.h"

clock_t start_timer(){
  clock_t before=clock();
  return before;
}

int time_difference(clock_t start_time){
  clock_t diff= clock()-start_time;
  int diff_sec=diff/CLOCKS_PER_SEC;
  return diff_sec;
}

void while_waiting_3_sec(Orders* orders){
  clock_t start_time=start_timer();
  while(time_difference(start_time)<3){
    get_pushed_button_switch_on_lights(orders);
    if(hardware_read_stop_signal()){
			hardware_command_stop_light(1);
		}
  }
}