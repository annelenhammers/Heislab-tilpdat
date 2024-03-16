#include "door.h"


Door door_constructor(DoorState doorstate) {
    Door door;
    door.doorstate = doorstate;
    return door;
}


void _openDoor(Door* door) {
    elevio_doorOpenLamp(1);
    door -> doorstate = OPEN;        
}

void close_door(Door* door) {
    if(door -> doorstate == OPEN) {
        elevio_doorOpenLamp(0);
        door -> doorstate = CLOSED;
    }
}
