#include "timer.h"

void timer_start(elevator* el){
    el->start_time = time(NULL);
}

int timer_check_times_up(elevator* el){
    time_t temp = time(NULL);
    int diff = (int)(temp - (el->start_time));
    if (diff >= DOOR_TIME){
        return 1;
    }
    else{
        return 0;
    }  
}   

