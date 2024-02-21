#include "elevator_cab.h"


void setMotor(Elevator_cab* elevator_cab) {
    if(elevator_cab -> direction == DIRN_STOP) {
        elevio_motorDirection(DIRN_STOP);
    }
    if (elevator_cab -> direction == DIRN_UP) {
        elevio_motorDirection(DIRN_UP);
    }
    if (elevator_cab -> direction == DIRN_DOWN) {
        elevio_motorDirection(DIRN_DOWN);
    }
}

void setState(Elevator_cab* elevator_cab, bool state) {
    elevator_cab -> state = state;
    

}
void getState(Elevator_cab* Elevator_cab) {

}




