/*!
 * @file main.c
 */

#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <time.h>
#include "driver/elevio.h"
#include "driver/elevator_cab.h"
#include "functionality.h"

/*!
 * @brief Main function
 * @details
 * - Before the while loop, the constructors and initilazers are called
 * - when the elevator is initialized, it is on the first floor. The direction is then set to DIRN_UP right before the loop
 * 1:
 * - floor of statemachine takes the value of the floor sensor
 * - updates the floor-lights
 * 2:
 * - checks if cab should stop at defined floors (!= -1)
 * - opens door, calls timer and closes door again
 * - Timer has logic to handle emergencies and obstruction-problems
 * - if it stopes, the order gets cleared from the buttons-array, and the order-lamp is turned off
 * 3: 
 * -
 * -
 * -
 * 4: the first foor-loop checks if any buttons are pressed on the floors above if direction is DIRN_UP/ below if direction is DIRN_DOWN 
 * - if yes, it jumps to dir_check using goto and sets stationary to false
 * 5: the second foor-loop checks if any buttons are pressed on the floors in the opposide direction of what the cab has/had before it stopped
 * - if yes, it sets the direction to the opposite as the one it has now, sets stationary to false and jumps to dir_check and 
 * 6: if neither of these conditions are met, it means that there are no more people in line/and stationary is set to true:
 * 7: dir_check
 * - if stationary is false, it sets the motor to drive in the direction stated in the statemachine
 * - if not, it stops the motor
 * 
 * @return 0 on successuful execution 
 */

int main() {

    elevio_init();

    Elevator_cab* elevator_cab = elevator_cab_constructor(read_current_floor(), DIRN_STOP); 
    Door door = door_constructor(0);
    // printf("door %p\n",(void *) &(door.doorstate));
    printf("door %i\n", door.doorstate);

    StateMachine state_machine = state_machine_constructor(*elevator_cab, door);
    printf("sm %i\n", state_machine.elevator_cab.floor);
    initialize_elevator_cab(elevator_cab);

    printf("=== Elevator Program is running ===\n");
    printf("Go through the requirements for the FAT-test\n");

    state_machine.elevator_cab.direction = DIRN_UP;  // initialiseres til første etasje, så setter neste direction til DIRN_UP

    while(1) {
        int floor = elevio_floorSensor();
        state_machine.elevator_cab.floor = floor; 

        if (state_machine.elevator_cab.floor != -1)
        {
            elevio_floorIndicator(state_machine.elevator_cab.floor);    //oppdaterer etasjelysene
            state_machine.prev_stop_floor = state_machine.elevator_cab.floor; //husker forrige floor
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
                   
                    state_machine.buttons[state_machine.elevator_cab.floor].button[i] = false; //clear order
                    elevio_buttonLamp(state_machine.elevator_cab.floor, i, 0); //clear lamp
                }     
            }
        }

        //polling the buttons and updating the state machine
        if (elevio_stopButton()){
            if(!state_machine.stopButton){ //hvis stopButton-state er false, settes lampa høg
                elevio_stopLamp(1);
            }
            state_machine.stopButton = true; //stopbutton-state settes høy
            state_machine.stationary = true; //stationary sier at heisen er stoppet, settes høy
            elevio_motorDirection(DIRN_STOP); //motoren stoppes
            for(int f = 0; f < N_FLOORS; f++){
                // printf("Polling buttons\n");
                for(int b = 0; b < N_BUTTONS; b++) {
                    state_machine.buttons[f].button[b] = 0; //alle bestillinger slettes
                    elevio_buttonLamp(f, b, 0); //alle lampene slukkes
                }
            }
            if (state_machine.elevator_cab.floor != -1)
            {
                _openDoor(&door); //dør åpnes hvis den er på et floor
                timer(3, &state_machine); //det er stopbuttonfunkjsonalitet i timer også, så den holdes åpen. skal vente 3 sek tilslutt
                close_door(&door); //denne kjøres når timer går ut og stopButton er lav igjen
            } else{
                continue; //hopper videre hvis mellom floors, skal ikke gjøre noe spes da
            }
        } else{
            if (state_machine.stopButton){ //hvis stop-state er høy og stoppknapp ikke er trykket, slukk lampa og set state lav
                elevio_stopLamp(0); 
                printf("Returning from alarm\n");
                state_machine.stopButton = false;
                // state_machine.stationary = false;
            }
            for(int f = 0; f < N_FLOORS; f++){
                // printf("Polling buttons\n");
                for(int b = 0; b < N_BUTTONS; b++) {
                    int btnPressed = elevio_callButton(f, b);
                    if (btnPressed) {
                        state_machine.buttons[f].button[b] = btnPressed; //ta bestillinger
                        elevio_buttonLamp(f, b, btnPressed); //slå på lampa
                    }
                }
            }
        }


        if (state_machine.elevator_cab.floor == -1){
            if (state_machine.stationary){ //Alarm restart only, hvis den har stoppa mellom floors er stationary true, så den må komme seg på plass igjen
                //printf("alarm restart\n");
                for (int i = state_machine.prev_stop_floor + state_machine.elevator_cab.direction; i >= 0 && i < N_FLOORS; i += state_machine.elevator_cab.direction){
                    for (int j = 0; j < N_BUTTONS; j++){
                        if (state_machine.buttons[i].button[j])
                        {
                            //printf("Stuck on floors1\n");   
                            state_machine.stationary = false;
                            goto dir_check;
                        }
                    }
                }
                for (int i = state_machine.prev_stop_floor; i >= 0 && i < N_FLOORS; i -= state_machine.elevator_cab.direction){
                    for (int j = 0; j < N_BUTTONS; j++){
                        if (state_machine.buttons[i].button[j])
                        {
                            //printf("Stuck on floors2\n");
                            //printf("on%d\n", state_machine.elevator_cab.floor);
                            //printf("cab_dir %d\n", state_machine.elevator_cab.direction);
                            state_machine.stationary = false;
                            state_machine.elevator_cab.direction = -state_machine.elevator_cab.direction;
                            //printf("cab_dir after %d\n", state_machine.elevator_cab.direction);
                            goto dir_check;
                        }
                    }
                }
            } else{
                goto dir_check;
            }
        }

        //sjekker floors over seg hvis den går oppover /under seg hvis den går nedover, og sjekker om noen form for knapp(opp,ned eller cab) er trykket
        for (int i = state_machine.elevator_cab.floor + state_machine.elevator_cab.direction; i >= 0 && i < N_FLOORS; i += state_machine.elevator_cab.direction){
            for (int j = 0; j < N_BUTTONS; j++){
                if (state_machine.buttons[i].button[j])
                {
                    //printf("Stuck on floors1\n");   
                    state_machine.stationary = false;
                    goto dir_check;
                }
            }
        }
        //sjekker floors i motsatt retning av direction
        for (int i = state_machine.elevator_cab.floor - state_machine.elevator_cab.direction; i >= 0 && i < N_FLOORS; i -= state_machine.elevator_cab.direction){
            for (int j = 0; j < N_BUTTONS; j++){
                if (state_machine.buttons[i].button[j])
                {
                    //printf("Stuck on floors2\n");
                    //printf("on%d\n", state_machine.elevator_cab.floor);
                    //printf("cab_dir %d\n", state_machine.elevator_cab.direction);
                    state_machine.stationary = false;
                    state_machine.elevator_cab.direction = -state_machine.elevator_cab.direction; //setter motsatt direction
                    //printf("cab_dir after %d\n", state_machine.elevator_cab.direction);
                    goto dir_check;
                }
            }
        }
        state_machine.stationary = true; //hvis ingen bestillinger, så skal motore stoppes

        dir_check:

        if (!state_machine.stationary)
        {
            elevio_motorDirection(state_machine.elevator_cab.direction);
            //printf("Setting dir %d\n", state_machine.elevator_cab.direction);
        } else {
            elevio_motorDirection(DIRN_STOP);
            // printf("Stopping\n");
        }
        
        nanosleep(&(struct timespec){0, 20*1000*100}, NULL);
    }
    return 0;
}
      
