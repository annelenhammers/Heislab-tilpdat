#pragma once

#include "time.h"
#include "panels.h"

typedef enum {
    OPEN = 1,
    CLOSED = 0
}DoorState;

typedef struct {
    DoorState doorstate;
    int obstruction;
}Door;

int getObstrctionState(Door* door);
void setDoorState(Door* door, DoorState doorstate);
void setObstructionState(Door* door, int obstruction);
void _openDoor(Door* door);
void close_door(Door* door);
void obstruction(Door* door);
void destroyDoor(Door* door);
void timer();
void initialize_door(Door* door, int obstruction);
Door* door_constructor(DoorState Door, int obstruction);
DoorState getDoorState(Door* door);



