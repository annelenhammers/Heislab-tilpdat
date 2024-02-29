#include "functionality.h"

StateMachine* state_machine_constructor(Elevator_cab* elevator_cab, Queue* queue, QueueState* queuestate, Elevator_panel* elevator_panel, Floor_Panel* floor_panel, Door* door) {
    StateMachine* statemachine = (StateMachine*)malloc(sizeof(StateMachine));
    statemachine -> door = door;
    statemachine -> elevator_cab = elevator_cab;
    statemachine -> elevator_panel = elevator_panel;
    statemachine -> floor_panel = floor_panel;
    statemachine -> queue = queue;
    statemachine -> queuestate = queuestate;
    return statemachine;
}

void initialize_state_machine(StateMachine* statemachine) {
    initialize_elevator_cab(statemachine -> elevator_cab);





}

