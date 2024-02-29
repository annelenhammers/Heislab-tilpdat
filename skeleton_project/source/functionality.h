#pragma once

#include "driver/elevator_cab.h"
#include "panels.h"
#include "queue.h"
#include "door.h"

typedef struct {
    Elevator_cab* elevator_cab;
    Queue* queue;
    QueueState* queuestate;
    Elevator_panel* elevator_panel;
    Floor_Panel* floor_panel;
    Door* door

}StateMachine;

StateMachine* state_machine_constructor(Elevator_cab* elevator_cab, Queue* queue, QueueState* queuestate, Elevator_panel* elevator_panel, Floor_Panel* floor_panel, Door* door);
void initialize_state_machine(StateMachine* statemachine);
void destroy_state_machine(StateMachine* statemachine);
