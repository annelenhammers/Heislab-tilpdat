#pragma once

#include "driver/elevator_cab.h"
#include "door.h"
#include "time.h"


struct AllButtons{
    bool button[N_BUTTONS]; //Array of 0: hall up, 1: hall down, 2: all cab buttons
};


typedef struct {
    Elevator_cab elevator_cab;
    Door door;

    struct AllButtons buttons[N_FLOORS]; 

    bool obstructed;
    bool stationary;
    bool stopButton;
} StateMachine;


StateMachine state_machine_constructor(Elevator_cab elevator_cab, Door door);
void initialize_state_machine(StateMachine* statemachine);

bool should_stop_this_floor(StateMachine* statemachine);
void timer(int sec, StateMachine *state_machine);

void execute_stop_at_floor(StateMachine *state_machine, Door *door);
void polling_buttons_and_update_statemachine(StateMachine *state_machine);
void check_direction(StateMachine *state_machine);