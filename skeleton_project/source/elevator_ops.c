#include "elevator_ops.h"



StateMachine state_machine_constructor(Elevator_cab elevator_cab, Door door) 
{
    StateMachine statemachine;
    statemachine.elevator_cab = elevator_cab;
    statemachine.door = door;

    for (int i = 0; i < N_FLOORS; i++)
    {
        for (int j = 0; j < N_BUTTONS; j++)
        {
            statemachine.buttons[i].button[j] = false;
        }
    } 
    return statemachine;
}

void initialize_state_machine(StateMachine* statemachine) {
    initialize_elevator_cab(&(statemachine -> elevator_cab));
}


//forklar de forskjellige tallene eller lag variabler for dem og erstatt det, å ta minus 1 og dele på minus 2
bool should_stop_this_floor(StateMachine* statemachine)
{   
    //checks if someone wants to join the elevator in the current direction at the current floor
    if (statemachine->buttons[statemachine->elevator_cab.floor].button[(statemachine->elevator_cab.direction-1)/-2])
    { 
        printf("Stopping, curr dir at curr floor\n");
        return true;
    }

    //someone wants to get off
    if (statemachine->buttons[statemachine->elevator_cab.floor].button[2])
    { 
        printf("Stopping, letting ppl off\n");
        return true;
    }

    for (int i = statemachine->elevator_cab.floor + statemachine->elevator_cab.direction; i >= 0 && i < N_FLOORS; i += statemachine->elevator_cab.direction)
    {
        //Check if should go past and pick up on the way back
        if(statemachine->buttons[i].button[0] || statemachine->buttons[i].button[1] || statemachine->buttons[i].button[2])
        {
            return false;
        }
    }

    //Going opposite direction
    if(statemachine->buttons[statemachine->elevator_cab.floor].button[(statemachine->elevator_cab.direction+1)/2]) 
    {
        printf("Stopping, going down\n");
        return true;
    }
    return false;
}


void timer(int sec, StateMachine *state_machine) 
{
    time_t start = time(NULL);
    time_t elapsed_time;
    printf("start time: %d\n", start);

    while (1) 
    {
        elapsed_time = time(NULL) - start;
        // printf("elapsed: %d\n", elapsed_time);

        if (elapsed_time >= sec) 
        {
            break;
        }

        if (elevio_stopButton())
        {
            // printf("Stopped\n");
            for(int f = 0; f < N_FLOORS; f++)
            {
                printf("stopping buttons\n");
                for(int b = 0; b < N_BUTTONS; b++) 
                {
                    state_machine->buttons[f].button[b] = 0;
                    elevio_buttonLamp(f, b, 0);
                }
            }
            start = time(NULL);
            continue;
        }

        // printf("Not stopped\n");
        if (elevio_obstruction())
        {
            start = time(NULL);
        }

        for(int f = 0; f < N_FLOORS; f++)
        {
            for(int b = 0; b < N_BUTTONS; b++) 
            {
                int btnPressed = elevio_callButton(f, b);
                if (btnPressed) 
                {
                    state_machine->buttons[f].button[b] = btnPressed;
                    elevio_buttonLamp(f, b, btnPressed);
                }
            }
        }
    }
}


void execute_stop_at_floor(StateMachine *state_machine, Door *door) {
    stopMotor();
    openDoor(door);
    timer(3, state_machine);
    close_door(door);

    printf("Stopping at floor %d\n", state_machine->elevator_cab.floor);
                
    for (int i = 0; i < N_BUTTONS; i++) 
    {
        state_machine->buttons[state_machine->elevator_cab.floor].button[i] = false;
        elevio_buttonLamp(state_machine->elevator_cab.floor, i, 0);
    }     
}

void polling_buttons_and_update_statemachine(StateMachine *state_machine) {
    
    for(int f = 0; f < N_FLOORS; f++)
    {
        // printf("Polling buttons\n");
        for(int b = 0; b < N_BUTTONS; b++) 
        {
            int btnPressed = elevio_callButton(f, b);
            if (btnPressed) 
            {
                state_machine->buttons[f].button[b] = btnPressed;
                elevio_buttonLamp(f, b, btnPressed);
            }
        }
    }
}

void check_direction(StateMachine *state_machine)
{
    if (state_machine->elevator_cab.floor == -1)
    {
        goto dir_check;
    }

    for (int i = state_machine->elevator_cab.floor + state_machine->elevator_cab.direction; i >= 0 && i < N_FLOORS; i += state_machine->elevator_cab.direction)
    {
        for (int j = 0; j < N_BUTTONS; j++)
        {
            if (state_machine->buttons[i].button[j])
            {
                printf("Stuck on floors1\n");   
                state_machine->stationary = false;
                goto dir_check;
            }
        }
    }
    
    for (int i = state_machine->elevator_cab.floor - state_machine->elevator_cab.direction; i >= 0 && i < N_FLOORS; i -= state_machine->elevator_cab.direction)
    {
        for (int j = 0; j < N_BUTTONS; j++)
        {
            if (state_machine->buttons[i].button[j])
            {
                printf("Stuck on floors2\n");
                printf("on%d\n", state_machine->elevator_cab.floor);
                printf("cab_dir %d\n", state_machine->elevator_cab.direction);
                state_machine->stationary = false;
                state_machine->elevator_cab.direction = -state_machine->elevator_cab.direction;
                printf("cab_dir after %d\n", state_machine->elevator_cab.direction);
                goto dir_check;
            }
        }
    }
    
    state_machine->stationary = true;

dir_check:
    if (!state_machine->stationary)
    {
        elevio_motorDirection(state_machine->elevator_cab.direction);
        printf("Setting dir %d\n", state_machine->elevator_cab.direction);

    } else {
        elevio_motorDirection(DIRN_STOP);
        // printf("Stopping\n");
    }
}