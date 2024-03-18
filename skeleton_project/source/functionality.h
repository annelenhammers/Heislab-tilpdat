/*! 
 * @file
 * @brief functionality.h keeps the final statemachine object and contains a timer functionality and logic for when the elevator is supposed to stop
*/
#pragma once

#include "driver/elevator_cab.h"
#include "door.h"
#include "time.h"

/*!
 * @brief Struct representing a collection of buttons
 * - @p button Array of size three that contains the boolean vaules for the buttons UP = 0, DOWN = 1 and CAB = 2
 */

struct AllButtons{

    bool button[N_BUTTONS];
};

/*!
 * @brief Struct representing a collection of states and buttons
 * @details 
 * - @c elevator_cab holds an @c Elevator_cab object
 * - @c door holds a @c Door object
 * - @c buttons  holds an @c Allbuttons object of size 4, representing the floors where each floor keeps a set of three buttons as described in @c AllButtons
 * - @p stationary Boolean variable that is true when the cab is stationary, and false otherwise
 * - @p stopButton Boolean variable that is true if the stopbutton is pressed, and false otherwise
 * - @p prev_stop_floor integer value representing the last floor the elevator stopped at 
 */

typedef struct {

    Elevator_cab elevator_cab;
    Door door;
    struct AllButtons buttons[N_FLOORS]; 
    bool stationary;
    bool stopButton;
    int prev_stop_floor;

} StateMachine;

/*!
 * @brief Constructs and returns an instance of a statemachine
 * @param[in] elevator_cab sets the elevator_cab member of an instance of @c Statemachine to the value of @p elevator_cab
 * @param[in] door sets the door member of an instance of @c Statemachine to the value of @p door
 * @return statemachine instance
 */

StateMachine state_machine_constructor(Elevator_cab elevator_cab, Door door);

/*!
 * @brief Physically initializes the elevator. Calls the "initilaize_elevator_cab"-function
 * @param[in] statemachine points to a statemachine object 
 */

void initialize_state_machine(StateMachine* statemachine);

/*!
 * @brief Determines whether the elevator should stop at the current floor
 * 
 * @param[in] statemachine Pointer to a statemachine object
 * @return true if the elevator should stop at the current floor, and false otherwise
 * @details
 * The four if-statements are executed sequentially:
 * - if someone wants to join the elevator in the current direction at the current floor, the elevator stops
 * - if someone wants to get off at the current floor, the elevator stops
 * - if none of the above if-statements have any hits, the elevator scans the buttons array, looking for orders on the floors above if direction is UP, and below if direction is DOWN, to check if it should go past the current floor
 * - if there are no orders above/below, the elevator may stop to pick up passengers going the opposite direction 
 */

bool should_stop_this_floor(StateMachine* statemachine);

/*!
 * @brief Timer.h can count a given amount of seconds, and handles button polling, door-obstructions and stopButton-cases
 * 
 * @param[in] seconds Amount of seconds the timer should count  
 * @param[in, out] state_machine Pointer to a @c StateMachine object
 * @details
 * - Time.h library is used for counting
 * - if three seconds has elapsed, it breaks the loop
 * - if the stopbutton is pressed, it constantly clears the Orderlist, and restarts the count. This is to ensure emergency functionality when timer is called in main
 * - if obstruction-sensor is activated, it restarts the count
 * - it also polls the orders so that orders can be registered when the timer is activated in main
 */

void timer(int seconds, StateMachine* state_machine);

