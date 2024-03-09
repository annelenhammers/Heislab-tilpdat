#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <time.h>
#include "driver/elevio.h"
#include "driver/elevator_cab.h"
#include "functionality.h"



int main() {

    elevio_init();

    Elevator_cab* elevator_cab = elevator_cab_constructor(read_current_floor(), DIRN_STOP, true); 
    Door door = door_constructor(0,0);
    printf("door %i\n", door.doorstate);

    StateMachine state_machine = state_machine_constructor(*elevator_cab, door);
    printf("sm %i\n", state_machine.elevator_cab.floor);
    
    initialize_elevator_cab(elevator_cab);

    printf("=== Elevator Program is running ===\n");
    printf("Go through the requirements for the FAT-test\n");

    state_machine.elevator_cab.direction = DIRN_UP;

    while(1) 
    {
        int floor = elevio_floorSensor();
        state_machine.elevator_cab.floor = floor;

        if (state_machine.elevator_cab.floor != -1)
        {
            elevio_floorIndicator(state_machine.elevator_cab.floor);
        }
        
        if(state_machine.elevator_cab.floor != -1) 
        {
            // printf("Checking if should stop\n");

            if(should_stop_this_floor(&state_machine)) 
            {
                
                stopMotor();
                _openDoor(&door);
                timer(3, &state_machine);
                close_door(&door);

                printf("Stopping at floor %d\n", state_machine.elevator_cab.floor);
                
                for (int i = 0; i < N_BUTTONS; i++) 
                {
                    state_machine.buttons[state_machine.elevator_cab.floor].button[i] = false;
                    elevio_buttonLamp(state_machine.elevator_cab.floor, i, 0);
                }     
            }
        }

        //polling the buttons and updating the state machine
        if (elevio_stopButton())
        {
            state_machine.stopButton = true;
            state_machine.stationary = true;
            elevio_motorDirection(DIRN_STOP);

            for(int f = 0; f < N_FLOORS; f++)
            {
                // printf("Polling buttons\n");
                for(int b = 0; b < N_BUTTONS; b++) 
                {
                    state_machine.buttons[f].button[b] = 0;
                    elevio_buttonLamp(f, b, 0);
                }
            }

            if (state_machine.elevator_cab.floor != -1)
            {
                _openDoor(&door);
                timer(3, &state_machine);
                close_door(&door);

            } else {
                continue;
            }

        } else {
            if (state_machine.stopButton)
            {
                printf("Returning from alarm\n");
                state_machine.stopButton = false;
                state_machine.stationary = false;
            }

            for(int f = 0; f < N_FLOORS; f++)
            {
                // printf("Polling buttons\n");
                for(int b = 0; b < N_BUTTONS; b++) 
                {
                    int btnPressed = elevio_callButton(f, b);
                    if (btnPressed) 
                    {
                        state_machine.buttons[f].button[b] = btnPressed;
                        elevio_buttonLamp(f, b, btnPressed);
                    }
                }
            }
        }

        if (state_machine.elevator_cab.floor == -1)
        {
            goto dir_check;
        }

        for (int i = state_machine.elevator_cab.floor + state_machine.elevator_cab.direction; i >= 0 && i < N_FLOORS; i += state_machine.elevator_cab.direction)
        {
            for (int j = 0; j < N_BUTTONS; j++)
            {
                if (state_machine.buttons[i].button[j])
                {
                    printf("Stuck on floors1\n");   
                    state_machine.stationary = false;
                    goto dir_check;
                }
            }
        }
        for (int i = state_machine.elevator_cab.floor - state_machine.elevator_cab.direction; i >= 0 && i < N_FLOORS; i -= state_machine.elevator_cab.direction)
        {
            for (int j = 0; j < N_BUTTONS; j++)
            {
                if (state_machine.buttons[i].button[j])
                {
                    printf("Stuck on floors2\n");
                    printf("on%d\n", state_machine.elevator_cab.floor);
                    printf("cab_dir %d\n", state_machine.elevator_cab.direction);
                    state_machine.stationary = false;
                    state_machine.elevator_cab.direction = -state_machine.elevator_cab.direction;
                    printf("cab_dir after %d\n", state_machine.elevator_cab.direction);
                    goto dir_check;
                }
            }
        }

        state_machine.stationary = true;

        dir_check:

        if (!state_machine.stationary)
        {
            elevio_motorDirection(state_machine.elevator_cab.direction);
            printf("Setting dir %d\n", state_machine.elevator_cab.direction);

        } else {
            elevio_motorDirection(DIRN_STOP);
            // printf("Stopping\n");
        }

        if(elevio_obstruction())
        {
            elevio_stopLamp(1);
        } else {
            elevio_stopLamp(0);
        }
        
        nanosleep(&(struct timespec){0, 20*1000*100}, NULL);
    }
    return 0;
}
