#include "elevator_cab.h"

void stop_motor() {
    MotorDirection direction = DIRN_STOP;
    elevio_motorDirection(direction);
}
void motor_up() {
    MotorDirection direction = DIRN_UP;
    elevio_motorDirection(direction);
}
void motor_down() {
    MotorDirection direction = DIRN_DOWN;
    elevio_motorDirection(direction);
}

