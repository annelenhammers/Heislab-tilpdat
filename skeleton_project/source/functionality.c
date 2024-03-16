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
    if (statemachine->buttons[statemachine->elevator_cab.floor].button[(statemachine->elevator_cab.direction-1)/-2]){ //magic math 🎩🪄  checks if someone wants to join the elevator in the current direction at the current floor
        printf("Stopping bc magic\n");
        return true;
    }
    if (statemachine->buttons[statemachine->elevator_cab.floor].button[2]){ //someone wants to get off
        
        printf("Stopping bc ppl escape\n");
        return true;
    }

    //hvis ingen av if-ene over er blitt kjørt, ser den etter ordre på etasjene over/under seg, og går forbi current floor hvis det er noen over/under seg som vil på
    //de som trykket ned når heis var på veg opp t.d vil bli plukket opp når heisen har snudd igjen, og første if kjøres

    for (int i = statemachine->elevator_cab.floor + statemachine->elevator_cab.direction; i >= 0 && i < N_FLOORS; i += statemachine->elevator_cab.direction)
    {
        if(statemachine->buttons[i].button[0] || statemachine->buttons[i].button[1] || statemachine->buttons[i].button[2])//Check if should go past and pick up on the way back
        {
            return false;
        }
    }
    // hvis ingen av dei andre if'ene matcha, kan heisen plukke opp dei som har trykket på knapp i motsatt av kjøreretning
    if(statemachine->buttons[statemachine->elevator_cab.floor].button[(statemachine->elevator_cab.direction+1)/2]) //Going opposite direction
    {
        printf("Stopping opposite\n");
        return true;
    }
    return false;
}


void timer(int seconds, StateMachine *state_machine) {
    time_t start = time(NULL);
    time_t elapsed_time;
    
    printf("start time: %d\n", start);

    while (1) {
        elapsed_time = time(NULL) - start;

        if (elapsed_time >= seconds) {
            break;
        }
        // Your other code goes here
        if (elevio_stopButton()){
            elevio_stopLamp(1);
            // printf("Stopped\n");
            for(int f = 0; f < N_FLOORS; f++){
                //printf("stopping buttons\n");
                for(int b = 0; b < N_BUTTONS; b++) {
                    state_machine->buttons[f].button[b] = 0;
                    elevio_buttonLamp(f, b, 0);
                }
            }
            start = time(NULL);
            continue;
        }
        // printf("Not stopped\n");
        if (elevio_obstruction()){
            start = time(NULL);
        }
        for(int f = 0; f < N_FLOORS; f++){
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
