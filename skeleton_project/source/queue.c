#include "queue.h"

void queue_update(elevator* el){
    for (int i = 0; i < HARDWARE_NUMBER_OF_FLOORS; i++){
        for (int j = 0; j < 3; j++){
            if (hardware_read_order(i, j)){ //Sjekker alle kombinasjoner av etasjer og bestillingstyper
                el->queue[i][j] = 1;
            }
        }
    }

    el->queue[HARDWARE_NUMBER_OF_FLOORS-1][0]=-1;
    el->queue[0][2]=-1;
}

void queue_clear_all(elevator* el){
    for (int i = 0; i < HARDWARE_NUMBER_OF_FLOORS; i++){
        for (int j = 0; j < HARDWARE_NUMBER_OF_BUTTONS;j++){
            el->queue[i][j]=0;
        }
    }

    el->queue[HARDWARE_NUMBER_OF_FLOORS-1][0]=-1;
    el->queue[0][2]=-1;
}

int queue_orders_at_floor(elevator* el){
    for(int i = 0; i < HARDWARE_NUMBER_OF_BUTTONS; i++){
        if(el->queue[el->currentfloor][i] == 1){
            return 1;
        }
    }
    return 0; 
}

int queue_orders_above(elevator* el){
    for(int i = el->currentfloor + 1; i < HARDWARE_NUMBER_OF_FLOORS; i++){
        for(int j = 0; j < HARDWARE_NUMBER_OF_BUTTONS; j++){
            if(el->queue[i][j] == 1){
                return 1;
            }
        }
    }
    return 0;
}

int queue_orders_below(elevator* el){
    for(int i = 0; i < el->currentfloor; i++){
        for(int j = 0; j < HARDWARE_NUMBER_OF_BUTTONS; j++){
            if(el->queue[i][j] == 1){
                return 1;
            }
        }
    }
    return 0;
}

int queue_take_order(elevator* el){
    if(el->queue[el->currentfloor][1] == 1){
        return 1;
    }

    switch (el->current_dir)
    {
    case HARDWARE_MOVEMENT_UP:
        if((el->queue[el->currentfloor][0]) || ((el->queue[el->currentfloor][2]) && !queue_orders_above(el))){
            return 1;
        }
        break;
    case HARDWARE_MOVEMENT_DOWN:
        if((el->queue[el->currentfloor][2]) || ((el->queue[el->currentfloor][0]) && !queue_orders_below(el))){
            return 1;
        }
        break;
    case HARDWARE_MOVEMENT_STOP:
        break;
    default:
        break;
    }
    return 0;
}

void queue_clear_executed_order(elevator* el){
    for(int i = 0; i < HARDWARE_NUMBER_OF_BUTTONS; i++){
        el->queue[el->currentfloor][i]=0;
        hardware_command_order_light(el->currentfloor, i, 0);
    }

    el->queue[HARDWARE_NUMBER_OF_FLOORS-1][0]=-1;
    el->queue[0][2]=-1;
}

void queue_set_light(elevator* el){
    for (int i = 0; i < HARDWARE_NUMBER_OF_FLOORS; i++){
        for (int j = 0; j < 3; j++){
            if(el->queue[i][j] == 1){
               hardware_command_order_light(i, j, 1); 
            }
        }
    }
}

void queue_clear_light(elevator* el){
    for (int i = 0; i < HARDWARE_NUMBER_OF_FLOORS; i++){
        for (int j = 0; j < 3; j++){
            if(el->queue[i][j] == 1){
               hardware_command_order_light(i, j, 0); 
            }
        }
    }
}

void queue_clear_all_lights(elevator* el){
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

void queue_print(elevator* el){
    printf("\n");
    for(int i = 0; i < HARDWARE_NUMBER_OF_BUTTONS; i++){
        for(int j = 0; j < HARDWARE_NUMBER_OF_FLOORS; j++){
            printf("%d\t", el->queue[j][i]);
        }
        printf("\n");
    }
    printf("\n");
}