#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <time.h>
#include "driver/elevio.h"
#include "driver/elevator_cab.h"
#include "elevator_ops.h"



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
        
        if (state_machine.elevator_cab.floor != -1) 
        {
            // printf("Checking if should stop\n");
            if(should_stop_this_floor(&state_machine)) 
            {
                execute_stop_at_floor(&state_machine, &door);   
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

            polling_buttons_and_update_statemachine(&state_machine);
        }

        check_direction(&state_machine);
        
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
