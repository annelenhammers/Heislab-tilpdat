#include "elevator_cab.h"

Elevator_cab elevator_cab;


int read_current_floor() {
    int floor = elevio_floorSensor();
    return floor;
}


void initialize_elevator_cab(Elevator_cab* elevator_cab) {
    while(read_current_floor() != FIRST_FLOOR) {
        elevator_cab -> floor = read_current_floor();
        elevator_cab -> direction = DIRN_DOWN;
        elevio_motorDirection(DIRN_DOWN);
        if(read_current_floor() == FIRST_FLOOR) {
            elevator_cab -> direction = DIRN_DOWN;
            elevator_cab -> floor = FIRST_FLOOR;
            elevio_motorDirection(DIRN_STOP);
            break;
        }
    }

    if(read_current_floor(elevator_cab) == FIRST_FLOOR) {
        elevator_cab -> direction = DIRN_STOP;
        elevio_motorDirection(DIRN_STOP);
        elevator_cab -> floor = FIRST_FLOOR;
    }
}

Elevator_cab* elevator_cab_constructor(Floor floor, MotorDirection direction) { 
    
    elevator_cab.floor = floor;
    elevator_cab.direction = direction;
    
    return &elevator_cab;
}









