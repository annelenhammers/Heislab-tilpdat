#include "elevator_cab.h"


void setMotor(Elevator_cab* elevator_cab) 
{
    if(elevator_cab -> state == false || elevator_cab -> direction == DIRN_STOP) 
    {
        elevio_motorDirection(DIRN_STOP);
    }

    if (elevator_cab -> direction == DIRN_UP) 
    {
        elevio_motorDirection(DIRN_UP);
    }

    if (elevator_cab -> direction == DIRN_DOWN) 
    {
        elevio_motorDirection(DIRN_DOWN);
    }
}

void setState(Elevator_cab* elevator_cab, bool state) 
{
    elevator_cab -> state = state;
    setMotor(elevator_cab);   
}

bool getState(Elevator_cab* elevator_cab) 
{
    return elevator_cab -> state;
}

void setDirection(Elevator_cab* elevator_cab, MotorDirection direction)
{
    elevator_cab -> direction = direction;
    setMotor(elevator_cab);
}

MotorDirection getDirection(Elevator_cab* elevator_cab) 
{
    return elevator_cab -> direction;
}

void _setFloor(Elevator_cab* elevator_cab, Floor floor) 
{
    elevator_cab -> floor = floor;
}

int read_current_floor() 
{
    int floor = elevio_floorSensor();
    return floor + 1;
}

Floor getFloor(Elevator_cab* elevator_cab) 
{
    return elevator_cab -> floor;
}


void initialize_elevator_cab(Elevator_cab* elevator_cab) 
{
    while(read_current_floor(elevator_cab) != FIRST_FLOOR) 
    {
        _setFloor(elevator_cab, read_current_floor(elevator_cab));
        setDirection(elevator_cab, DIRN_DOWN);

        if(read_current_floor(elevator_cab) == FIRST_FLOOR) 
        {
            setDirection(elevator_cab, DIRN_STOP);
            break;
        }
    }

    if(read_current_floor(elevator_cab) == FIRST_FLOOR) 
    {
        setDirection(elevator_cab, DIRN_STOP);
        _setFloor(elevator_cab, FIRST_FLOOR);
    }
    //legg til stoppknapp-funksjonalitet 
}

Elevator_cab* elevator_cab_constructor(Floor floor, MotorDirection motordirection, bool state) 
{
    Elevator_cab* elevator_cab = (Elevator_cab*)malloc(sizeof(Elevator_cab));
    
    if (elevator_cab == NULL)
    {
        fprintf(stderr, "Error: the elevator cab's memory allocation failed\n");
        return NULL;
    }
    elevator_cab -> floor = floor;
    elevator_cab -> direction = motordirection;
    elevator_cab -> state = state;   
    return elevator_cab;
}

void delete_elevator_cab(Elevator_cab* elevator_cab) 
{
    free(elevator_cab);    
}










