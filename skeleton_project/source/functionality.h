#pragma once

#include "driver/elevator_cab.h"
#include "panels.h"
// #include "queue.h"
#include "door.h"

struct AllButtons{
    bool button[N_BUTTONS];
};

typedef struct {
    Elevator_cab* elevator_cab;
    // Queue* queue;
    // QueueState* queue_state;
    // Elevator_panel* elevator_panel;
    // Floor_Panel* floor_panel;
    Door* door;
    struct AllButtons buttons[N_FLOORS];

}StateMachine;

StateMachine* state_machine_constructor(Elevator_cab* elevator_cab, Door* door);
void initialize_state_machine(StateMachine* statemachine);
void destroy_state_machine(StateMachine* statemachine);
bool should_stop_this_floor(StateMachine* statemachine);
