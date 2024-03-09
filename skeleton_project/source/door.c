#include "door.h"


Door door_constructor(DoorState doorstate, int obstruction) {
    Door door;
    door.doorstate = doorstate;
    door.obstruction = obstruction;
    return door;
}

DoorState getDoorState(Door* door) {
    return door -> doorstate;
}

int getObstructionState(Door* door) {
    return door -> obstruction;
}

void setDoorState(Door* door, DoorState doorstate) {
    door -> doorstate = doorstate;   
}

void setObstructionState(Door* door, int obstruction) {
    door -> obstruction = obstruction;
}

void _openDoor(Door* door) {
    elevio_doorOpenLamp(1);
    setDoorState(door, OPEN);        
}

void close_door(Door* door) {
    if(door -> doorstate == OPEN) {
        elevio_doorOpenLamp(0);
        setDoorState(door, CLOSED);
    }
}

void obstruction(Door* door) {

    while(elevio_obstruction() == 1 && door -> doorstate == OPEN) {
        _openDoor(door);
    }

    close_door(door);
}

void initialize_door(Door* door, int obstruction) {
    *door = door_constructor(CLOSED, 0);
    close_door(door);
}
