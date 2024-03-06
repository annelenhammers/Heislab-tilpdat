#pragma once

#include "time.h"
// #include "panels.h"



typedef enum {
   
    OPEN = 1,
    CLOSED = 0

} DoorState;



typedef struct {

    DoorState doorstate;
    int obstruction;

} Door;




int getObstructionState(Door* door);
void setObstructionState(Door* door, int obstruction);

void setDoorState(Door* door, DoorState doorstate);
DoorState getDoorState(Door* door);

void _openDoor(Door* door);
void close_door(Door* door);
void obstruction(Door* door); //det er en funksjon og en int?
void timer(int sec);

void initialize_door(Door* door, int obstruction);
Door door_constructor(DoorState Door, int obstruction);

//void destroyDoor(Door* door);


