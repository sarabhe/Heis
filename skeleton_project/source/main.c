#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include "fsm.h" 

int main(){
    printf("=== Heis-prosjekt ===\n");
    printf("Press ctrl + c to exit the program\n");

    elevator el;
    fsm_init(&el);
    fsm_switch(&el);
    
    return 0;
}
