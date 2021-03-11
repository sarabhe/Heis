/**
 * @file
 * @brief The finite state machine.
 */

#ifndef FSM_H
#define FSM_H
#include "timer.h"
#include "elevator.h"


/**
 * @brief Initializes the elevator and moves it to a defined state.
 * @param[in, out] el The elevator.
 */
void fsm_init(elevator* el);

/**
 * @brief Loop that controls the elevator. Contains the logic for the finite state machine.
 * @param[in, out] el The elevator.
 */
void fsm_switch(elevator* el);

/**
 * @brief Function called when the elevator is in state IDLE.
 * If there is a request at current floor, enters state @c DOOR_OPEN. 
 * Otherwise if there is a request above or below, enters state @c MOVE.
 * @param[in, out] el The elevator. 
 */
void fsm_idle(elevator* el);

/**
 * @brief Function called when the elevator is in state MOVE. 
 * Sets direction and starts the motor.
 * If the elevator should take order at current floor, enters state @c IDLE.
 * @param[in, out] el The elevator.
 */
void fsm_move(elevator* el);

/**
 * @brief Function called when the elevator is in state DOOR OPEN. 
 * Commands door open, starts the timer and checks for any obstructions. 
 * Closes the door when the time is up and clears excecuted orders. 
 * Then enters state @c IDLE.
 * @param[in, out] el The elevator.
 */
void fsm_door_open(elevator* el);

/**
 * @brief Function called when the elevator is in state EMERGENCY STOP. 
 * Stops the elevator and sets the stop light.
 * Clears the queue. 
 * If the elevator is at a floor the door is opened and when the stop button is released the 
 * elevator enters state @c DOOR_OPEN. Otherwise it awaits until 
 * any requests is made, and then enters @c MOVE.
 * @param[in, out] el The elevator.
 */
void fsm_emergency_stop(elevator* el);


#endif
