#pragma once

#include "elevio.h"
#include "con_load.h"
#include <stdbool.h>
#include <stdio.h>

typedef enum {
    FIRST_FLOOR =  1,
    SECOND_FLOOR = 2,
    THIRD_FLOOR = 3,
    FOURTH_FLOOR = 4
}Floor;

typedef struct 
{
    Floor floor;
    MotorDirection direction;
    bool state;                 //state = true; active state = false; inactive

}Elevator_cab;

void setMotor(Elevator_cab* elevator_cab);
void setState(Elevator_cab* elevator_cab, bool state);
bool getState(Elevator_cab* elevator_cab);
void setDirection(Elevator_cab* elevator_cab, MotorDirection direction);
MotorDirection getDirection(Elevator_cab* elevator_cab);
int read_current_floor();
void _setFloor(Elevator_cab* elevator_cab, Floor floor);
Floor getFloor(Elevator_cab* elevator_cab);
void delete_elevator_cab(Elevator_cab* elevator_cab);
void initialize_elevator_cab(Elevator_cab* elevator_cab);
Elevator_cab* elevator_cab_constructor(Floor floor, MotorDirection motordirection, bool state);




