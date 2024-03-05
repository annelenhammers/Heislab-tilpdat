#include "elevator_cab.h"

Elevator_cab* elevator_cab(enum states current_state, MotorDirection current_dir, MotorDirection prev_dir, int inactive) {
    Elevator_cab* cab = (Elevator_cab*)malloc(sizeof(Elevator_cab));
    cab -> current_direction = current_dir;
    cab -> current_state = current_state;
    cab -> prev_direction = prev_dir;
    cab -> inactive = inactive;
}


int intialize_elevator_cab(Elevator_cab* cab) {
    elevator_cab(INIT, DIRN_STOP, DIRN_STOP, 0);
    if(cab -> current_floor != FIRST_FLOOR) {
        elevio_motorDirection(DIRN_DOWN);
        return 0;
    }
    elevio_motorDirection(DIRN_STOP);
    return 1;
}

void floor_update(Elevator_cab* cab) {
    int current = cab -> current_floor;
    current = elevio_floorSensor();
    if(current != INBETWEEN) {
        cab -> prev_floor = cab -> latest_floor;
        cab -> latest_floor = current;
    }
}

void next_floor(Elevator_cab* cab, int next_floor) {
    if(next_floor > cab -> latest_floor) {
        elevio_motorDirection(DIRN_UP);
    }
    if(next_floor < cab -> latest_floor) {
        elevio_motorDirection(DIRN_DOWN);
    }
    if(next_floor == cab -> latest_floor && cab -> current_floor == INBETWEEN && cab -> prev_direction == DIRN_UP) {
        elevio_motorDirection(DIRN_DOWN);
        cab ->current_direction = DIRN_DOWN;
        next_floor = cab -> latest_floor+1;
    }
    if(next_floor == cab -> latest_floor && cab -> current_floor == -1 && cab -> prev_direction == DIRN_DOWN) {
        elevio_motorDirection(DIRN_UP);
        cab ->current_direction = DIRN_UP;
        next_floor = cab -> latest_floor - 1;
    }

}

void next_direction(Elevator_cab* cab) {
    cab -> next_stop = queue_find_floor();
    if (cab -> next_stop > cab -> latest_floor) {
        cab -> current_direction = DIRN_UP;
    }
    if (cab -> next_stop < cab -> latest_floor) {
        cab -> current_direction = DIRN_DOWN;
    }
    if (cab -> next_stop  == cab -> latest_floor) {
        cab -> current_direction = DIRN_STOP;
    }

}

void beyond_next_stop(Elevator_cab* cab) {
    if(cab -> current_direction == DIRN_UP) {
        for(int i = cab -> next_stop + 1; i < N_FLOORS; i++) {
            if(queue[i][1] == 1) {
                cab -> next_stop = i;
            }
            if(queue[i][2] == 1) {
                cab -> next_stop = i;
            }
        }

    }
    if(cab -> current_direction == DIRN_DOWN) {
        for(int i = 0; i < cab -> next_stop; i++) {
            if(queue[i][0] == 1) {
                cab -> next_stop = i;
            }
            if(queue[i][2] == 1) {
                cab -> next_stop = i;
            }
        }
    }
}

int at_valid_floor(Elevator_cab* cab) {
    if((queue[cab -> latest_floor][cab -> current_direction] == 1 || queue[cab->latest_floor][2] == 1) && cab ->current_floor != -1) {
        return 1;
    }

    return 0;
}

void run(Elevator_cab* cab) {
    floor_update(cab);
    ipdate_floor_lights(cab);
    switch (cab ->current_state) {

        case (INIT):
            if(intialize_elevator_cab(cab)) {
                cab -> current_state = NOT_MOVING;
            }
            break;

        case (NOT_MOVING):
            add_order();
            if(elevio_stopButton()) {
                cab -> current_state = EMERGENCY;
            }
            if(!queue_is_empty()) {
                cab -> current_state = MOVING;
            }
            break;
        case(MOVING):
            add_order();
            if(cab -> current_direction == DIRN_STOP) {
                next_direction(cab);
            }
            if(cab -> latest_floor == cab -> next_stop && cab -> current_floor != -1) {
                cab -> current_state = DOOR_OPEN;
                cab -> current_direction = DIRN_STOP;
            }
            beyond_next_stop(cab);
            if(at_valid_floor(cab)) {
                cab -> current_state = DOOR_OPEN;
            }
            next_floor(cab, cab->next_stop);
            if(elevio_stopButton()) {
                cab -> current_state = EMERGENCY;
                cab -> prev_direction = cab -> current_direction;
                cab -> current_direction = DIRN_STOP;
            }
            break;
        case(DOOR_OPEN):
            add_order();
            if(elevio_stopButton()) {
                cab ->current_state = EMERGENCY;
            }
            elevio_motorDirection(DIRN_STOP);
            elevio_doorOpenLamp(1);
            clear_floor(cab -> latest_floor);
            timer_start(0);
            if(elevio_obstruction()) {
                timer_start(1);
            }
            if(timer_times_up(2) && !elevio_obstruction()) {
                cab -> current_state = NOT_MOVING;
                elevio_doorOpenLamp(0);
            }
            break;
        case(EMERGENCY):
            elevio_motorDirection(DIRN_STOP);
            elevio_stopLamp(1);
            queue_initializer();
            if(cab -> current_floor == cab -> latest_floor) {
                if(!elevio_stopButton()) {
                    elevio_stopLamp(0);
                    cab -> current_state = DOOR_OPEN;
                }
                else {
                    elevio_doorOpenLamp(1);
                }
            }
            else {
                if(!elevio_stopButton()) {
                    elevio_stopLamp(0);
                    cab -> current_state = NOT_MOVING;
                }
            }
            if(elevio_stopButton()) {
                timer_start(0);
                if(timer_times_up(5)) {
                    cab -> current_state = INACTIVE;
                }
            }
            break;
        case(INACTIVE):
            elevio_doorOpenLamp(0);
            elevio_floorIndicator(0);
            elevio_stopLamp(0);
            cab -> inactive = 1;
            break;
    }
}












