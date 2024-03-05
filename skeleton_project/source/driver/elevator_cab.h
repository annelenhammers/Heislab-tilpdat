#pragma once

#include "elevio.h"
#include "../lights.h"
#include "queue.h"
#include "timer.h"

enum Floor
{
    FIRST_FLOOR =  0,
    SECOND_FLOOR = 1,
    THIRD_FLOOR = 2,
    FOURTH_FLOOR = 3,
    INBETWEEN = -1

};

enum states {
    INIT,
    NOT_MOVING,
    MOVING,
    OBSTRUCTION,
    EMERGENCY,
    DOOR_OPEN,
    INACTIVE
};

typedef struct 
{   
    int inactive;
    MotorDirection current_direction;
    MotorDirection prev_direction;
    enum states current_state;
    enum Floor prev_floor;
    enum Floor current_floor;
    enum Floor latest_floor;
    enum Floor next_stop;

} Elevator_cab;


Elevator_cab* elevator_cab(enum states current_state, MotorDirection current_dir, MotorDirection prev_dir, int inactive);
int intialize_elevator_cab(Elevator_cab* elevator_cab);
void next_floor(Elevator_cab* cab, int next_floor);
void next_direction(Elevator_cab* cab);
void beyond_next_stop(Elevator_cab* cab);
int at_valid_floor(Elevator_cab* cab);
void run(Elevator_cab* cab);