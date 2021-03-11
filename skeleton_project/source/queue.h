/**
 * @file
 * @brief Takes care of the elevator's queue. 
 */

#ifndef QUEUE_H
#define QUEUE_H
#include "states.h"


/**
 * @brief Updates the queue with new orders. 
 * @param[in, out] el The elevator.
 */
void queue_update(elevator* el);

/**
 * @brief Clears all orders (0). Unavaliable orders are given the value -1. 
 * @param[in, out] el The elevator.
 */
void queue_clear_all(elevator* el);

/**
 * @brief Checks if the queue contains any orders at its current floor. 
 * @param[in] el The elevator.
 * @return 1 for success, 0 for failure.
 */
int queue_orders_at_floor(elevator* el);

/**
 * @brief Checks if the queue contains any orders above its current floor. 
 * @param[in] el The elevator.
 * @return 1 for success, 0 for failure.
 */
int queue_orders_above(elevator* el);

/**
 * @brief Checks if the queue contains any orders below its current floor. 
 * @param[in] el The elevator.
 * @return 1 for success, 0 for failure.
 */
int queue_orders_below(elevator* el);

/**
 * @brief Checks if the elevator should take the order at current floor.
 * @param[in, out] el The elevator.
 * @return 1 for success, 0 for failure.
 */
int queue_take_order(elevator* el);

/**
 * @brief Deletes executed orders at current floor. 
 * @param[in, out] el The elevator.
 */
void queue_clear_executed_order(elevator* el);

/**
 * @brief Sets the order lights of the buttons that have been pulled. 
 * @param[in, out] el The elevator.
 */
void queue_set_light(elevator* el);

/**
 * @brief Clears the order lights for executed orders.
 * @param[in, out] el The elevator.
 */
void queue_clear_light(elevator* el);

/**
 * @brief Clears all order lights.
 * @param[in, out] el The elevator.
 */
void queue_clear_all_lights(elevator* el);

/**
 * @brief Prints the queue as a matrix. 
 * @param[in] el The elevator.
 */
void queue_print(elevator* el);


#endif // #ifndef QUEUE_H


