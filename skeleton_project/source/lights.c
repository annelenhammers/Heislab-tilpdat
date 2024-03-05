#include "lights.h"

void ipdate_floor_lights(Elevator_cab* cab) {
    elevio_floorIndicator(cab -> latest_floor);
}