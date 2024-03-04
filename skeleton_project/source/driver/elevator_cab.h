#pragma once

#include "elevio.h"
#include "con_load.h"
#include <stdbool.h>
#include <stdio.h>
#include "../door.h"

typedef enum 
{
    FIRST_FLOOR =  1,
    SECOND_FLOOR = 2,
    THIRD_FLOOR = 3,
    FOURTH_FLOOR = 4

} Floor;

typedef struct 
{
    Floor floor;
    MotorDirection direction;

} Elevator_cab;

void setMotor(Elevator_cab* elevator_cab);
void stopMotor();
void MotorUp();
void MotorDown();


void setDirection(Elevator_cab* elevator_cab, MotorDirection direction);
int read_current_floor();
void _setFloor(Elevator_cab* elevator_cab, Floor floor);
void delete_elevator_cab(Elevator_cab* elevator_cab);
void initialize_elevator_cab(Elevator_cab* elevator_cab);
Elevator_cab* elevator_cab_constructor(Floor floor, MotorDirection motordirection);
void stopButtonPressed(Elevator_cab* elevator_cab, Door* door);




