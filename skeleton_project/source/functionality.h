/*! 
 * @file
 * @brief Functionality keeps the final statemachine object and has does operations 
 * when the elevator is supposed to stop
*/
#pragma once

#include "driver/elevator_cab.h"
#include "door.h"
#include "time.h"

/*!
 * @brief @c ALLButtons Struct representing a collection of buttons
 * @details 
 * - @p button Array of size three contains the boolean vaules for the buttons UP, DOWN and  
 */

struct AllButtons{

    bool button[N_BUTTONS];
};

/*!
 * @brief @c StateMachine Struct representing a collection of states
 * @details 
 * - @c elevator_cab @c Elevator_cab object
 * - @c door @c Door object
 * - @c buttons @c Allbuttons object of size 4 representing the floors, each floor keeps a set of three buttons
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


StateMachine state_machine_constructor(Elevator_cab elevator_cab, Door door);


void initialize_state_machine(StateMachine* statemachine);

/*!
 * @brief Determines whether the elevator should stop at the current floor
 * 
 * @param[in] statemachine is a pointer to the statemachine object, and holds elevator_cab object with the cab's last direction, current floor, and also keeps the button-array
 * @return true if the elevator should stop at the current floor, and false otherwise
 * @details
 * The four if-statements are executed sequentially:
 * - if someone wants to join the elevator in the current direction at the current floor, the elvator stops
 * - if someone wants to get off at the current floor, the elevator stops
 * - if none of the above if-statements have hits, the elevator scans the button array, looking for orders on the floors above if direction is UP, and below if direction is DOWN, to check if it should go past the current floor
 * - if there are no orders above/below, the elevator may stop to pick up passangers going the opposite direction 
 */

bool should_stop_this_floor(StateMachine* statemachine);

/*!
 * @brief Timer can count a given amount of seconds, and handles door-obstructions and emergencies
 * 
 * @param @p seconds Amount of seconds the timer should count  
 * @param[in, out] @p state_machine Pointer to a @c StateMachine object
 * @details
 * - if three seconds has elapsed, it breaks the loop
 * - if the stopbutton is pressed, it constantly clears the Orderlist, and restarts the count. This is to ensure emergency functionality when timer is called in main
 * - if obstruction-sensor is activated, it restarts the count
 * - it also polls the Orderlist as so that orders can be registered when the timer is activated in main
 */

void timer(int seconds, StateMachine* state_machine);

