#include "timer.h"

void start_timer(elevator* el){
    el->start_time = time(NULL);
}

int times_up(elevator* el){
    time_t temp = time(NULL);
    int diff = (int)(temp - (el->start_time));
    if (diff >= DOOR_TIME){
        return 1;
    }
    else{
        return 0;
    }  
}   

