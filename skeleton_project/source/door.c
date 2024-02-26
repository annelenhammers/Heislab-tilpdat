#include "door.h"


DoorState getDoorState(Door* door) {
    return door -> doorstate;
}
int getObstrctionState(Door* door) {
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
    clock_t start;
    double time;
    while(time = (double)(clock() - start) / CLOCKS_PER_SEC <= 3.0){ }
    elevio_doorOpenLamp(0);
    setDoorState(door, CLOSED);
}

void obstruction(Door* door) {
    while(elevio_obstruction() == 1 && door -> doorstate == OPEN) {
        elevio_doorOpenLamp(1);
        if(elevio_doorOpenLamp() == 0) {
            _openDoor(door);
        }
    }
}

void destroyDoor(Door* door) {
    free(door);
}

//må implementere stopp-funskjonalitet(implementeres i elevator_cab())
//må implementere at dør skal vere lukka når active = false (implementeres i elevator_cab())


