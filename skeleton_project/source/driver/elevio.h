#pragma once


#define N_FLOORS 4

typedef enum { 
    DIRN_DOWN   = -1,
    DIRN_STOP   = 0,
    DIRN_UP     = 1
} MotorDirection;


#define N_BUTTONS 3

typedef enum { 
    BUTTON_HALL_UP      = 0,
    BUTTON_HALL_DOWN    = 1,
    BUTTON_CAB          = 2
} ButtonType;


void elevio_init(void); //initialiserer heissystemet

void elevio_motorDirection(MotorDirection dirn); //får motor til å bevege seg i angitt retning
void elevio_buttonLamp(int floor, ButtonType button, int value); // setter lys til alle knapper
void elevio_floorIndicator(int floor); // oppdaterer etasjeindikator
void elevio_doorOpenLamp(int value); // value er 0 eller 1, kontrollerer lampelys (på/av)
void elevio_stopLamp(int value); // value er 0 eller 1, kontrollerer stopplys (på/av)

int elevio_callButton(int floor, ButtonType button); //sjekker at knapp er trykket
int elevio_floorSensor(void); //gir ut etasjestate
int elevio_stopButton(void); //gir stoppbutton-state
int elevio_obstruction(void); //gir ut obsruksjonsstate

