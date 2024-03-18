#include "functionality.h"


StateMachine state_machine_constructor(Elevator_cab elevator_cab, Door door) {
    
    StateMachine statemachine;
    statemachine.elevator_cab = elevator_cab;
    statemachine.door = door;

    for (int i = 0; i < N_FLOORS; i++){
        for (int j = 0; j < N_BUTTONS; j++){
            statemachine.buttons[i].button[j] = false;
        }
    }    
    return statemachine;
}

void initialize_state_machine(StateMachine* statemachine) {
    initialize_elevator_cab(&(statemachine -> elevator_cab));
}

bool should_stop_this_floor(StateMachine* statemachine){
    if (statemachine->buttons[statemachine->elevator_cab.floor].button[(statemachine->elevator_cab.direction-1)/-2]){ //Checks if someone wants to join the elevator in the current direction at the current floor
        return true;
    }
    if (statemachine->buttons[statemachine->elevator_cab.floor].button[2]){ //someone wants to get off
        return true;
    }

    for (int i = statemachine->elevator_cab.floor + statemachine->elevator_cab.direction; i >= 0 && i < N_FLOORS; i += statemachine->elevator_cab.direction)
    {
        if(statemachine->buttons[i].button[0] || statemachine->buttons[i].button[1] || statemachine->buttons[i].button[2])//Check if should go past and pick up on the way back
        {
            return false;
        }
    }
    if(statemachine->buttons[statemachine->elevator_cab.floor].button[(statemachine->elevator_cab.direction+1)/2]) //Going opposite direction
    {
        return true;
    }
    return false;
}


void timer(int seconds, StateMachine *state_machine) {
    time_t start = time(NULL);
    time_t elapsed_time;

    while (1) {
        elapsed_time = time(NULL) - start;

        if (elapsed_time >= seconds) {
            break;
        }
        if (elevio_stopButton()){   //stopButton
            elevio_stopLamp(1);
            for(int f = 0; f < N_FLOORS; f++){
                for(int b = 0; b < N_BUTTONS; b++) {
                    state_machine->buttons[f].button[b] = 0;
                    elevio_buttonLamp(f, b, 0);
                }
            }
            start = time(NULL);
            continue;
        }
        if (elevio_obstruction()){  //Obstruction -> start over again
            start = time(NULL);
        }
        for(int f = 0; f < N_FLOORS; f++){  //polls the order buttons and adds them to the button-array
            for(int b = 0; b < N_BUTTONS; b++) {
                int btnPressed = elevio_callButton(f, b);
                if (btnPressed) {
                    state_machine->buttons[f].button[b] = btnPressed;
                    elevio_buttonLamp(f, b, btnPressed);
                }
            }
        }
    }
}
