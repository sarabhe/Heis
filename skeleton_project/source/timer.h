/**
 * @file
 * @brief Functions to keep the door open for a period of time.
 */

#ifndef TIMER_H
#define TIMER_H
#include <time.h>
#include <stdio.h>
#include "states.h"
#define DOOR_TIME 3

/**
 * @brief Starts the timer. 
 * @param[in, out] el The elevator.
 */
void timer_start(elevator* el);

/**
 * @brief Checks if the time is up. 
 * @param[in, out] el The elevator.
 * @return 1 if the time is up, 0 if not. 
 */
int timer_check_times_up(elevator* el);

#endif // #ifndef TIMER_H


