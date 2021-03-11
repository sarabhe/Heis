/**
 * @file
 * @brief Provides communication between the elevator and the hardware.
 */

#ifndef ELEVATOR_H
#define ELEVATOR_H
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include "hardware.h"
#include "queue.h"


/**
 * @brief Gets the current floor.
 * @return -1 if the elevator is between floors, otherwise the floor's index.
 */
int elev_get_current_floor();

/**
 * @brief Sets the current floor when the elevator arrives at a new
 * floor.
 * @param[in, out] el The elevator.
 */
void elev_set_current_floor(elevator* el);

/**
 * @brief Sets the floor indicator light for the current floor. 
 * If the elevator is between floors, the floor 
 * indicator light is lit for the previous floor.
 * @param[in] el The elevator.
 */
void elev_set_floor_indicator(elevator* el);

/**
 * @brief Sets the motor direction depending on previous
 * direction and next orders.
 * @param[in] el The elevator.
 * @return @c HARDWARE_MOVEMENT_UP, @c HARDWARE_MOVEMENT_STOP, @c HARDWARE_MOVEMENT_DOWN
 */
HardwareMovement elev_set_motor_dir(elevator* el);

/**
 * @brief Updates previous and current direction.
 * @param[in, out] el The elevator.
 */
void elev_update_dir(elevator* el);

/**
 * @brief Secures that the elevator does not move past
 * its range by changing the motor direction when it reaches 
 * the top/bottom floor.
 * @param[in, out] el The elevator.
 */
void elev_control_range(elevator* el);




#endif // ##ifndef ELEVATOR_H
