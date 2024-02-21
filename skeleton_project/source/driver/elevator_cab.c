#include "elevator_cab.h"


void setMotor(Elevator_cab* elevator_cab) {
    if(elevator_cab -> state == false) {
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
    setMotor(elevator_cab);   
}
bool getState(Elevator_cab* elevator_cab) {
    return elevator_cab -> state;
}

void setDirection(Elevator_cab* elevator_cab, MotorDirection direction) {
    elevator_cab -> direction = direction;
    setMotor(elevator_cab);
}

MotorDirection getDirection(Elevator_cab* elevator_cab) {
    return elevator_cab ->direction;
}

void setFloor(Elevator_cab* elevator_cab) {
    int floor = elevio_floorSensor();
    elevator_cab -> floor = floor;
}

Floor getFloor(Elevator_cab* elevator_cab) {
    return elevator_cab -> floor;
}
void delete_elevator_cab(Elevator_cab* elevator_cab) {
    free(elevator_cab);    
}









