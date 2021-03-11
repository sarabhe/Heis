#include "fsm.h"

void fsm_init(elevator* el){
    int error = hardware_init();
    if(error != 0){
        fprintf(stderr, "Unable to initialize hardware\n");
        exit(1);
    }

    while(elev_get_current_floor() == -1){
        hardware_command_movement(HARDWARE_MOVEMENT_DOWN);
    }
    hardware_command_movement(HARDWARE_MOVEMENT_STOP);

    queue_clear_all_lights(el);
    el->current_dir = HARDWARE_MOVEMENT_STOP; 
    el->currentfloor = elev_get_current_floor();
    queue_clear_all(el);
    el->state = IDLE;
}


void fsm_switch(elevator* el){

    while(1){

        if(hardware_read_stop_signal()){
            el->state = EMERGENCY_STOP;
        }

        elev_set_floor_indicator(el); 
        queue_update(el);
        queue_set_light(el);

        switch(el->state){
            case IDLE:
                fsm_idle(el);
                break;
            case MOVE:
                fsm_move(el);
                break;
            case DOOR_OPEN:
                fsm_door_open(el);
                break;
            case EMERGENCY_STOP:
                fsm_emergency_stop(el);
                break;
        }
    } 

} 

void fsm_idle(elevator* el){
    hardware_command_movement(HARDWARE_MOVEMENT_STOP);
    if(queue_orders_at_floor(el)){
        el->state = DOOR_OPEN;
    }
    else if(queue_orders_above(el) || queue_orders_below(el)){
        el->state = MOVE;
    }
    
    return;
}

void fsm_move(elevator* el){
    elev_control_range(el);
    elev_update_dir(el);
    hardware_command_movement(el->current_dir);
    elev_set_current_floor(el); 

    if(elev_get_current_floor(el)!=-1 && el->previousfloor!=el->currentfloor){ 
        if(queue_take_order(el)){
            el->state = IDLE;
        }
    }
}


void fsm_door_open(elevator* el){
    hardware_command_door_open(1);

    start_timer(el);
    while (1)
    {
        queue_update(el);
        queue_set_light(el);
        
        if(hardware_read_stop_signal()){
            el->state = EMERGENCY_STOP;
            break;
        }
        if(hardware_read_obstruction_signal()){
            return;
        }
        if(times_up(el)){
            break;
        }

    }
    hardware_command_door_open(0);
    queue_clear_executed_order(el);


    el->state = IDLE;
    

}

void fsm_emergency_stop(elevator* el){
    hardware_command_movement(HARDWARE_MOVEMENT_STOP);
    

    if(elev_get_current_floor(el)!=-1){
        hardware_command_door_open(1);
    }


    while (hardware_read_stop_signal()){
        hardware_command_stop_light(1);
    }
    
    queue_clear_light(el);
    queue_clear_all(el);
    hardware_command_stop_light(0);

    if(elev_get_current_floor(el)!=-1){
        el->state=DOOR_OPEN;
    }
    else{
        queue_update(el);
        queue_set_light(el);
        if(queue_orders_above(el) || queue_orders_below(el) || queue_orders_at_floor(el)){
            if(el->current_dir == HARDWARE_MOVEMENT_UP && queue_orders_at_floor(el)){
                el->currentfloor++;
            }
            else if(el->current_dir == HARDWARE_MOVEMENT_DOWN && queue_orders_at_floor(el)){
                el->currentfloor--;
            }
            el->state = MOVE;
        }
        else{
            return;
        }
    }
}

