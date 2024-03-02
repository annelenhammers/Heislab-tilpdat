#include "functionality.h"

StateMachine* state_machine_constructor(Elevator_cab* elevator_cab, Door* door) {
    StateMachine* statemachine = (StateMachine*)malloc(sizeof(StateMachine));
    statemachine -> door = door;
    statemachine -> elevator_cab = elevator_cab;
    // statemachine -> elevator_panel = elevator_panel;
    // statemachine -> floor_panel = floor_panel;
    // statemachine -> queue = queue;
    // statemachine -> queue_state = queue_state;
    for (int i = 0; i < N_FLOORS; i++)
    {
        for (int j = 0; j < N_BUTTONS; j++)
        {
            statemachine->buttons[i].button[j] = false;
        }
    }    
    return statemachine;
}

void initialize_state_machine(StateMachine* statemachine) {
    initialize_elevator_cab(statemachine -> elevator_cab);

}

bool should_stop_this_floor(StateMachine* statemachine){
    if (statemachine->elevator_cab->direction == 0) //stationary -> undefined behaviour
    {
        printf("Stopping bc stopped");
        return true;
    }
    if ((statemachine -> elevator_cab -> floor == N_FLOORS-1 && statemachine -> elevator_cab -> direction == DIRN_UP)|| //going up at top floor
        (statemachine -> elevator_cab -> floor == 0 && statemachine -> elevator_cab -> direction == DIRN_DOWN)) //going down at bottom floor
    {
        printf("Stopping bc cant fly/dig");
        return true; //Please don't let the elevator escape the building
    }
    if (statemachine->buttons[statemachine->elevator_cab->floor].button[(statemachine->elevator_cab->direction-1)/-2]){ //magic math 🎩🪄  checks if someone wants to join the elevator in the current direction at the current floor
        printf("Stopping bc magic");
        return true;
    }
    if (statemachine->buttons[statemachine->elevator_cab->floor].button[2]){ //someone wants to get off
        printf("Stopping bc ppl escape");
        return true;
    }
    for (int i = statemachine->elevator_cab->floor + statemachine->elevator_cab->direction; i >= 0 && i < N_FLOORS; i += statemachine->elevator_cab->direction)
    {
        if(statemachine->buttons[i].button[0] || statemachine->buttons[i].button[1] || statemachine->buttons[i].button[2])//Check if should go past and pick up on the way back
        {
            return false;
        }
    }
    if(statemachine->buttons[statemachine->elevator_cab->floor].button[(statemachine->elevator_cab->direction+1)/2]) //Going opposite direction
    {
        return true;
    }
    return false;
}