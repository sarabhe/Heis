/**
 * @file
 * @brief Creates a struct for the elevator and an enumerator for its different states.
 */

#ifndef STATES_H
#define STATES_H
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <time.h>
#include "hardware.h"



/**
 * @brief The elevators different states.
 * @p IDLE, @p MOVE, @p DOOR_OPEN, @p EMERGENCY_STOP
 */ 
typedef enum elev_state{
    IDLE,
    MOVE,
    DOOR_OPEN,
    EMERGENCY_STOP
} elev_state;


/**
 * @brief A structure to represent the elevator. Contains
 * memory of current state, queue of orders and time, as well
 * as current and previous floor and direction.
 */
typedef struct elevator{
    elev_state state;
    int previousfloor;
    int currentfloor;
    int queue[HARDWARE_NUMBER_OF_FLOORS][HARDWARE_NUMBER_OF_BUTTONS];
    HardwareMovement previous_dir;
    HardwareMovement current_dir;
    time_t start_time;
} elevator;

#endif // ##ifndef STATES_H