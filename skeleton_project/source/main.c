/*!
 * @file main.c
 *@details
 * see comments in the code
 */

#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <time.h>
#include "driver/elevio.h"
#include "driver/elevator_cab.h"
#include "functionality.h"

int main() {

    elevio_init();

    Elevator_cab* elevator_cab = elevator_cab_constructor(read_current_floor(), DIRN_STOP); 
    Door door = door_constructor(0);
    StateMachine state_machine = state_machine_constructor(*elevator_cab, door);

    initialize_elevator_cab(elevator_cab);

    printf("=== Elevator Program is running ===\n");

    state_machine.elevator_cab.direction = DIRN_UP;  //The elevator is initialized to first floor, so the direction state is set to DIRN_UP

    while(1) {
        int floor = elevio_floorSensor();
        state_machine.elevator_cab.floor = floor; //floor-state is set to the floor sensor value at the start of each loop

        if (state_machine.elevator_cab.floor != -1)
        {
            elevio_floorIndicator(state_machine.elevator_cab.floor);    //updates the floor lights on the panel
            state_machine.prev_stop_floor = state_machine.elevator_cab.floor; //prev_stop_floor variable is set to the current floor-state so that the last defined floor is stored
        }
        
        if(state_machine.elevator_cab.floor != -1) {           
            if(should_stop_this_floor(&state_machine)) {  
                
                stopMotor();
                open_Door(&door);
                timer(3, &state_machine); //timer has its own properties to take care of orders and obstruction and stop cases
                close_door(&door);

                for (int i = 0; i < N_BUTTONS; i++) {
                    state_machine.buttons[state_machine.elevator_cab.floor].button[i] = false; //clear order
                    elevio_buttonLamp(state_machine.elevator_cab.floor, i, 0); //clear lamp
                }     
            }
        }

        //if StopButton is pressed
        if (elevio_stopButton()){

            if(!state_machine.stopButton){ //if the stopButton-variable is false, the stopLamp is set high
                elevio_stopLamp(1);
            }

            state_machine.stopButton = true; //stopbutton is set high
            state_machine.stationary = true; //stationary is set high as the elevator is stopped
            stopMotor();                     //motor is stopped

            for(int f = 0; f < N_FLOORS; f++){
                for(int b = 0; b < N_BUTTONS; b++) {
                    state_machine.buttons[f].button[b] = 0; //all orders gets deleted
                    elevio_buttonLamp(f, b, 0); //all lampes are turned off
                }
            }
            if (state_machine.elevator_cab.floor != -1)
            {
                open_Door(&door); //door opens if the elevator is at a defined floor
                timer(3, &state_machine); //door is kept open until stopButton is false again, see timer function. It waits another 3 seconds when stopButton is false
                close_door(&door); //Door closes when timer is finished
            } 
            else {
                continue; //if the elevator is in between floors, it continues to the next step
            }
        } 

        else{
            if (state_machine.stopButton){ //if stopButtons isn't pressed anymore, but the stopButton variable is still set high, stoplamp is turned off and stopButton is set low
                elevio_stopLamp(0); 
                state_machine.stopButton = false;
            }
            for(int f = 0; f < N_FLOORS; f++){
                for(int b = 0; b < N_BUTTONS; b++) {
                    int btnPressed = elevio_callButton(f, b);
                    if (btnPressed) {
                        state_machine.buttons[f].button[b] = btnPressed; //take orders
                        elevio_buttonLamp(f, b, btnPressed); //turn on lamp if orders are taken
                    }
                }
            }
        }


        if (state_machine.elevator_cab.floor == -1){
            if (state_machine.stationary){ //Alarm restart only, if the elevator stopped in between floors
                for (int i = state_machine.prev_stop_floor + state_machine.elevator_cab.direction; i >= 0 && i < N_FLOORS; i += state_machine.elevator_cab.direction){ //checks floors above/below the previous known floor, depending on its last direction
                    for (int j = 0; j < N_BUTTONS; j++){
                        if (state_machine.buttons[i].button[j]) //if any buttons are pressed, stationary is set false, and it jumps to dir_check
                        { 
                            state_machine.stationary = false;
                            goto dir_check;
                        }
                    }
                }
                for (int i = state_machine.prev_stop_floor; i >= 0 && i < N_FLOORS; i -= state_machine.elevator_cab.direction){ //checks floors in opposite direction of the last known direction
                    for (int j = 0; j < N_BUTTONS; j++){
                        if (state_machine.buttons[i].button[j]) //if any buttons are pressed, stationary is set false, and the direction-state is set to the opposite of what initially was, and it jumps to dir_check
                        {
                            state_machine.stationary = false;
                            state_machine.elevator_cab.direction = -state_machine.elevator_cab.direction;
                            goto dir_check;
                        }
                    }
                }
            } 
            else{               //if the elevator is just inbetween floors, jump to goto_dir
                goto dir_check;
            }
        }

        //checks floors in the same direction first
        for (int i = state_machine.elevator_cab.floor + state_machine.elevator_cab.direction; i >= 0 && i < N_FLOORS; i += state_machine.elevator_cab.direction){
            for (int j = 0; j < N_BUTTONS; j++){
                if (state_machine.buttons[i].button[j])
                { 
                    state_machine.stationary = false; //stationary is set false, so that in dir_check the motor isnt stopped
                    goto dir_check;
                }
            }
        }
        //checks floor in the opposite direction
        for (int i = state_machine.elevator_cab.floor - state_machine.elevator_cab.direction; i >= 0 && i < N_FLOORS; i -= state_machine.elevator_cab.direction){
            for (int j = 0; j < N_BUTTONS; j++){
                if (state_machine.buttons[i].button[j])
                {
                    state_machine.stationary = false;
                    state_machine.elevator_cab.direction = -state_machine.elevator_cab.direction; //sets the direction as the opposite, and jumps to dir_check
                    goto dir_check;
                }
            }
        }
        state_machine.stationary = true; //if there are no more orders, none of the if-conditions above is takes, and the motor is to be stopped until more order arrive

        dir_check:

        if (!state_machine.stationary)
        {
            elevio_motorDirection(state_machine.elevator_cab.direction); 
        } else {
            elevio_motorDirection(DIRN_STOP);
        }
        
        nanosleep(&(struct timespec){0, 20*1000*100}, NULL);
    }
    return 0;
}
      
