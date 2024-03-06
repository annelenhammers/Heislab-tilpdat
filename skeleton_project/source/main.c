#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <time.h>
#include "driver/elevio.h"
#include "driver/elevator_cab.h"
#include "functionality.h"


#define modified_N_FLOORS 8

int floorpanel[modified_N_FLOORS][2] = {
    {-1,-1},{-1,-1},
    {-1,-1},{-1,-1},
    {-1,-1},{-1,-1},
    {-1,-1},{-1,-1}  
};
int elevatorpanel[N_FLOORS] = {-1,-1,-1,-1};


int main(){

    elevio_init();

    Elevator_cab* elevator_cab = elevator_cab_constructor(read_current_floor(), DIRN_STOP, true); 
    Door door = door_constructor(0,0);
    printf("door %p\n",(void *) &(door.doorstate));

    StateMachine state_machine = state_machine_constructor(*elevator_cab, door);
    printf("sm %p\n", (void *) &(state_machine.elevator_cab.floor));
    
    initialize_elevator_cab(&elevator_cab);
    //interrupt void ISR(void); kaaa faen er detta for no

    printf("=== Elevator Program is running ===\n");
    printf("Go through the requirements for the FAT-test\n");

    elevio_motorDirection(DIRN_UP);

    while(1){
        int floor = elevio_floorSensor();
        state_machine.elevator_cab.floor = floor;
        state_machine.elevator_cab.direction = DIRN_UP;
        // if(floor == 0){
        //     state_machine->elevator_cab->direction = DIRN_UP;
        // }
        // if(floor == N_FLOORS-1){
        //     state_machine->elevator_cab->direction = DIRN_DOWN;
        // }
        // elevio_motorDirection(state_machine->elevator_cab->direction);
        
        bool hasPendingOrder = false;
        for(int f = 0; f < modified_N_FLOORS; f++) {
            
            for(int b = 0; b < N_BUTTONS; b++) {
                
                if (((b == BUTTON_HALL_UP) || (b == BUTTON_HALL_DOWN)) && floorpanel[f][b] == 1) {
                    
                    if (state_machine.elevator_cab.direction != -1) {
                        
                        hasPendingOrder = true;
                    
                    }
                } else if (elevatorpanel[f] == 1) {
                    
                    if (state_machine.elevator_cab.direction != 1) {
                        
                        hasPendingOrder = true;
                    
                    }
                }
            }
        }
        if (hasPendingOrder) {
            if(state_machine.elevator_cab.direction != 0 && state_machine.elevator_cab.floor != -1) {
            
                printf("Checking if should stop\n");

                if(should_stop_this_floor(&state_machine)) {
                
                    stopMotor();
                    _openDoor(&door);
                    timer(3);
                    close_door(&door);

                    printf("Stopping at floor %d\n", state_machine.elevator_cab.floor);
                
                    for (int i = 0; i < N_BUTTONS; i++) {
                   
                        state_machine.buttons[state_machine.elevator_cab.floor].button[i] = false;
                        elevio_buttonLamp(state_machine.elevator_cab.floor, i, 0);
                    } 
                    /*for (int i = 0; i < N_BUTTONS; i++) {
                        if((i == BUTTON_HALL_UP || i == BUTTON_HALL_DOWN) && floorpanel[state_machine.elevator_cab.floor[i] == 1]) {
                            floorpanel[state_machine.elevator_cab.floor][i] = 0;
                            elevio_buttonLamp(state_machine.elevator_cab.floor, i, 0);
                        } else if (i == BUTTON_CAB && elevatorpanel[state_machine.elevator_cab.floor] == 1) {
                            elevatorpanel[state_machine.elevator_cab.floor] = 0;
                            elevio_buttonLamp(state_machine.elevator_cab.floor, BUTTON_CAB, 0);

                        }
                    }*/    
                }
            }


            //polling the buttons and updating the state machine
        for(int f = 0; f < N_FLOORS; f++){
            // printf("Polling buttons\n");
            for(int b = 0; b < N_BUTTONS; b++) {
                int btnPressed = elevio_callButton(f, b);
                if (btnPressed) {
                    state_machine.buttons[f].button[b] = btnPressed;
                    elevio_buttonLamp(f, b, btnPressed);

                    //clearing all pressed button in the state machine and turning off corresponding lamps
                    if ((b ==BUTTON_HALL_UP || b == BUTTON_HALL_DOWN) && floorpanel [f][b] == 1) {
                        floorpanel[f][b] = 0;
                        elevio_buttonLamp(f,b,0);
                    } else if (b == BUTTON_CAB && elevatorpanel[f] == 1) {
                        elevatorpanel[f] = 0;
                        elevio_buttonLamp(f, BUTTON_CAB, 0);
                    }
                }
            }
        }

        //Updating direction based on orders
        if(hasPendingOrder) {
            //moving
            elevio_motorDirection(state_machine.elevator_cab.direction);
        } else {
            //stationary
            bool hasPendingOrderOppositeDirn = false;
            for(int f = 0; f < modified_N_FLOORS; f++) {
                for(int b = 0; b < N_BUTTONS; b++) {
                    if ((b == BUTTON_HALL_UP || b == BUTTON_HALL_DOWN) && floorpanel[f][b] == 1) {
                        // now we check if there are orders in opposite direction
                        if (state_machine.elevator_cab.direction == DIRN_UP && b == BUTTON_HALL_DOWN) {
                            hasPendingOrderOppositeDirn = true;
                        } else if (state_machine.elevator_cab.direction == DIRN_DOWN && b == BUTTON_HALL_UP) {
                            hasPendingOrderOppositeDirn = true;
                        }
                    }
                }
            }
            
            if(hasPendingOrderOppositeDirn){
                bool isOrderAbove = false;
                bool isOrderBelow = false;
                //continue tommorow, i have to sleep
                state_machine.elevator_cab.direction = -state_machine.elevator_cab.direction;
                elevio_motorDirection(state_machine.elevator_cab.direction);
            } else {
                //if no more orders, stop elevator - go to defined state?
                elevio_motorDirection(DIRN_STOP);
            }

        }

        if(elevio_obstruction()) {
            elevio_stopLamp(1);
        } else {
            elevio_stopLamp(0);
        }

        if(elevio_stopButton()) {
            stopMotor();
            break;
        }

        elevio_floorIndicator(state_machine.elevator_cab.floor);

        nanosleep(&(struct timespec){0, 20*1000*100}, NULL);
    }
        

        /*
        if(state_machine.elevator_cab.direction != 0 && state_machine.elevator_cab.floor != -1) {
            
            printf("Checking if should stop\n");

            if(should_stop_this_floor(&state_machine)) {
                
                stopMotor();
                _openDoor(&door);
                timer(3);
                close_door(&door);

                printf("Stopping at floor %d\n", state_machine.elevator_cab.floor);
                
                for (int i = 0; i < N_BUTTONS; i++) {
                   
                    state_machine.buttons[state_machine.elevator_cab.floor].button[i] = false;
                    elevio_buttonLamp(state_machine.elevator_cab.floor, i, 0);
                }     
            }
        }


        //polling the buttons and updating the state machine
        for(int f = 0; f < N_FLOORS; f++){
            // printf("Polling buttons\n");
            for(int b = 0; b < N_BUTTONS; b++) {
                int btnPressed = elevio_callButton(f, b);
                if (btnPressed) {
                    state_machine.buttons[f].button[b] = btnPressed;
                    elevio_buttonLamp(f, b, btnPressed);
                }
            }
        }



        if (state_machine.elevator_cab.floor == -1){
            goto dir_check;
        }
        for (int i = state_machine.elevator_cab.floor + state_machine.elevator_cab.direction; i >= 0 && i < N_FLOORS; i += state_machine.elevator_cab.direction){
            // printf("Stuck on floors1");
            for (int j = 0; j < N_BUTTONS; j++){
                if (state_machine.buttons[i].button[j])
                {
                    state_machine.stationary = false;
                    goto dir_check;
                }
            }
        }
        for (int i = state_machine.elevator_cab.floor + state_machine.elevator_cab.direction; i >= 0 && i < N_FLOORS; i -= state_machine.elevator_cab.direction){
            // printf("Stuck on floors2");
            for (int j = 0; j < N_BUTTONS; j++){
                if (state_machine.buttons[i].button[j])
                {
                    state_machine.stationary = false;
                    state_machine.elevator_cab.direction = -state_machine.elevator_cab.direction;
                    goto dir_check;
                }
            }
        }
        state_machine.stationary = true;

        dir_check:

        if (!state_machine.stationary)
        {
            elevio_motorDirection(state_machine.elevator_cab.direction);
            printf("Setting dir");
        } else {
            elevio_motorDirection(DIRN_STOP);
            printf("Stopping");
        }

        if(elevio_obstruction()){
            elevio_stopLamp(1);
        } else {
            elevio_stopLamp(0);
        }
        
        if(elevio_stopButton()){
            stopMotor();
            break;
        }
        elevio_floorIndicator(state_machine.elevator_cab.floor);
        
        nanosleep(&(struct timespec){0, 20*1000*100}, NULL);*/
    }

    return 0;
}

