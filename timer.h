#include <timer.h>
#include <stdlib.h>
#include "movement.h"

void start_timer(Elevator elevator){
  clock_t before=clock();
  elevtor.start_time=before;
}

void time_difference(clock_t start_time, Elevator elevator){
  clock_t diff= clock()-start_time;
  int diff_sec=diff/CLOCKS_PER_SEC;
  elevator.timer_sec=diff;
}

int check_timer_3_sec(Elevator elevator){
  if (elevator.timer_sec>3){
    return 1;
  }
  return 0;
}
