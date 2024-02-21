#pragma once

#include "elevio.h"
#include "con_load.h"
#include "floor.h"
#include <stdbool.h>
#include <stdio.h>



typedef struct 
{
    Floor floor;
    MotorDirection direction;
    bool state;

}Elevator_cab;

void setMotor(Elevator_cab* elevator_cab);

void setState(Elevator_cab* elevator_cab, bool state);
void getState(Elevator_cab* Elevator_cab);
void setDirection(Elevator_cab* elevator_cab, MotorDirection direction);
void getDirection(Elevator_cab* elevator_cab);
void setFloor(Elevator_cab* elevator_cab, Floor floor );
void getFloor();
void delete_elevator_cab();



