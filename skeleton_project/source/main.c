#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <time.h>
#include "driver/elevio.h"
#include "driver/elevator_cab.h"
#include "functionality.h"



///////////should probably move the panels to panel module///////////

int main() {

    elevio_init();

    Elevator_cab* elevator_cab = elevator_cab_constructor(read_current_floor(), DIRN_STOP, true); 
    Door door = door_constructor(0,0);
    // printf("door %p\n",(void *) &(door.doorstate));
    printf("door %i\n", door.doorstate);

    StateMachine state_machine = state_machine_constructor(*elevator_cab, door);
    printf("sm %i\n", state_machine.elevator_cab.floor);
    
    initialize_elevator_cab(elevator_cab);
    //interrupt void ISR(void); kaaa faen er detta for no

    printf("=== Elevator Program is running ===\n");
    printf("Go through the requirements for the FAT-test\n");

    state_machine.elevator_cab.direction = DIRN_UP;

    while(1) {
        int floor = elevio_floorSensor();
        state_machine.elevator_cab.floor = floor;

        if (state_machine.elevator_cab.floor != -1)
        {
            elevio_floorIndicator(state_machine.elevator_cab.floor);
        }
        
        if(state_machine.elevator_cab.floor != -1) {
            
            // printf("Checking if should stop\n");

            if(should_stop_this_floor(&state_machine)) {
                
                stopMotor();
                _openDoor(&door);
                timer(3, &state_machine);
                close_door(&door);

                printf("Stopping at floor %d\n", state_machine.elevator_cab.floor);
                
                for (int i = 0; i < N_BUTTONS; i++) {
                   
                    state_machine.buttons[state_machine.elevator_cab.floor].button[i] = false;
                    elevio_buttonLamp(state_machine.elevator_cab.floor, i, 0);
                }     
            }
        }


        //polling the buttons and updating the state machine
        if (elevio_stopButton()){
            state_machine.stopButton = true;
            state_machine.stationary = true;
            elevio_motorDirection(DIRN_STOP);
            for(int f = 0; f < N_FLOORS; f++){
                // printf("Polling buttons\n");
                for(int b = 0; b < N_BUTTONS; b++) {
                    state_machine.buttons[f].button[b] = 0;
                    elevio_buttonLamp(f, b, 0);
                }
            }
            if (state_machine.elevator_cab.floor != -1)
            {
                _openDoor(&door);
                timer(3, &state_machine);
                close_door(&door);
            } else{
                continue;
            }
        } else{
            if (state_machine.stopButton){
                printf("Returning from alarm\n");
                state_machine.stopButton = false;
                state_machine.stationary = false;
            }
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
        }

        if (state_machine.elevator_cab.floor == -1){
            goto dir_check;
        }
        for (int i = state_machine.elevator_cab.floor + state_machine.elevator_cab.direction; i >= 0 && i < N_FLOORS; i += state_machine.elevator_cab.direction){
            for (int j = 0; j < N_BUTTONS; j++){
                if (state_machine.buttons[i].button[j])
                {
                    printf("Stuck on floors1\n");   
                    state_machine.stationary = false;
                    goto dir_check;
                }
            }
        }
        for (int i = state_machine.elevator_cab.floor - state_machine.elevator_cab.direction; i >= 0 && i < N_FLOORS; i -= state_machine.elevator_cab.direction){
            for (int j = 0; j < N_BUTTONS; j++){
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

        if(elevio_obstruction()){
            elevio_stopLamp(1);
        } else {
            elevio_stopLamp(0);
        }
        
        nanosleep(&(struct timespec){0, 20*1000*100}, NULL);
    }
    return 0;
}
        
    



// if(floor == 0){
        //     state_machine->elevator_cab->direction = DIRN_UP;
        // }
        // if(floor == N_FLOORS-1){
        //     state_machine->elevator_cab->direction = DIRN_DOWN;
        // }
        // elevio_motorDirection(state_machine->elevator_cab->direction);
        
//         bool hasPendingOrder = false;
//         int button_equivalent_direction = ((state_machine.elevator_cab.direction == DIRN_UP) ? BUTTON_HALL_UP : BUTTON_HALL_DOWN);
//         for(int f = 0; f < N_FLOORS; f++) {
            
//             for(int b = 0; b < N_BUTTONS; b++) {
                
//                 if ((b == button_equivalent_direction) && state_machine.buttons[f].button[b] == 1) {
//                     if (state_machine.elevator_cab.direction != -1) {  
//                         hasPendingOrder = true;  
//                     } /*else if (elevatorpanel[f] == 1) {
                        
//                         if (state_machine.elevator_cab.direction != 1) {
                            
//                             hasPendingOrder = true;
                        
//                         }
//                     }*/
//                 }
//             }
//         }
//         if (hasPendingOrder) {
//             if(state_machine.elevator_cab.direction != 0 && state_machine.elevator_cab.floor != -1) {
            
//                 printf("Checking if should stop\n");

//                 if(should_stop_this_floor(&state_machine)) {
                
//                     stopMotor();
//                     _openDoor(&door);
//                     timer(3);
//                     close_door(&door);

//                     printf("Stopping at floor %d\n", state_machine.elevator_cab.floor);
                
//                     for (int i = 0; i < N_BUTTONS; i++) {
                   
//                         state_machine.buttons[state_machine.elevator_cab.floor].button[i] = false;
//                         elevio_buttonLamp(state_machine.elevator_cab.floor, i, 0);
//                     } 
//                     /*for (int i = 0; i < N_BUTTONS; i++) {
//                         if((i == BUTTON_HALL_UP || i == BUTTON_HALL_DOWN) && floorpanel[state_machine.elevator_cab.floor[i] == 1]) {
//                             floorpanel[state_machine.elevator_cab.floor][i] = 0;
//                             elevio_buttonLamp(state_machine.elevator_cab.floor, i, 0);
//                         } else if (i == BUTTON_CAB && elevatorpanel[state_machine.elevator_cab.floor] == 1) {
//                             elevatorpanel[state_machine.elevator_cab.floor] = 0;
//                             elevio_buttonLamp(state_machine.elevator_cab.floor, BUTTON_CAB, 0);

//                         }
//                     }*/    
//                 }
//             }
//         }

//             //polling the buttons and updating the state machine
//         for(int f = 0; f < N_FLOORS; f++){
//             // printf("Polling buttons\n");
//             for(int b = 0; b < N_BUTTONS; b++) {
//                 int btnPressed = elevio_callButton(f, b);
//                 if (btnPressed) {
//                     state_machine.buttons[f].button[b] = btnPressed;
//                     elevio_buttonLamp(f, b, btnPressed);

//                     //clearing all pressed button in the state machine and turning off corresponding lamps
//                     if (b == button_equivalent_direction && state_machine.buttons[f].button[b] == 1) {
//                         state_machine.buttons[f].button[b] == 0;
//                         elevio_buttonLamp(f,b,0);
//                     } 
//                 }
//             }
//         }

//         //Updating direction based on orders
//         if(hasPendingOrder) {
//             //moving
//             elevio_motorDirection(state_machine.elevator_cab.direction);
//         } else {
//             //stationary
//             bool hasPendingOrderOppositeDirn = false;
//             for(int f = 0; f < N_FLOORS; f++) {
//                 for(int b = 0; b < N_BUTTONS; b++) {
//                     if ((b == button_equivalent_direction) && state_machine.buttons[f].button[b] == 1) {
//                         // now we check if there are orders in opposite direction
//                         if (state_machine.elevator_cab.direction == DIRN_UP && b == BUTTON_HALL_DOWN) {
//                             hasPendingOrderOppositeDirn = true;
//                         } else if (state_machine.elevator_cab.direction == DIRN_DOWN && b == BUTTON_HALL_UP) {
//                             hasPendingOrderOppositeDirn = true;
//                         }
//                     }
//                 }
//             }
//             //im not sure about the ! for the following if statement
//             if(!hasPendingOrderOppositeDirn){
//                 bool isOrderAbove = false;
//                 bool isOrderBelow = false;
//                 //are there any pending orders above or below current floor?
//                 for(int f = state_machine.elevator_cab.floor + 1; f < N_FLOORS; f++) {
//                     for(int b = 0; b < N_BUTTONS; b++){
//                         if ((b == button_equivalent_direction) && state_machine.buttons[f].button[b] == 1) {
//                             isOrderAbove = true;
//                             break;
//                         }
//                     }
//                     if(isOrderAbove) {
//                         break;
//                     }
//                 }
//                 for(int f = state_machine.elevator_cab.floor - 1; f >= 0; f--) {
//                     for(int b = 0; b < N_BUTTONS; b++) {
//                         if ((b == button_equivalent_direction) && state_machine.buttons[f].button[b] == 1) {
//                             isOrderBelow = true;
//                             break;
//                         }
//                     }
//                     if(isOrderBelow) {
//                         break;
//                     }
//                 }

//                 //change dir if no more orders above/below
//                 if (!isOrderAbove && !isOrderBelow) {
//                     state_machine.elevator_cab.direction = -state_machine.elevator_cab.direction;
//                     elevio_motorDirection(state_machine.elevator_cab.direction);
//                 } else {
//                     //seems like there are more pending orders above/below
//                     //keep moving in the current dir
//                     elevio_motorDirection(state_machine.elevator_cab.direction);
//                 }
//             } else {
//                 //seems like there are orders in opposite dir, change dir
//                 state_machine.elevator_cab.direction = -state_machine.elevator_cab.direction;
//                 elevio_motorDirection(state_machine.elevator_cab.direction);

//             }
//                 //if no more orders, stop elevator - go to defined state?
//                 elevio_motorDirection(DIRN_STOP);
            

//         }

//         if(elevio_obstruction()) {
//             elevio_stopLamp(1);
//         } else {
//             elevio_stopLamp(0);
//         }

//         if(elevio_stopButton()) {
//             stopMotor();
//             break;
//         }

//         elevio_floorIndicator(state_machine.elevator_cab.floor);

//         nanosleep(&(struct timespec){0, 20*1000*100}, NULL);
//     }
        
//     return 0;
// }