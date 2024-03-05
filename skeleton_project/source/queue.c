#include "queue.h"

void queue_initializer() {
    for(int i = 0; i < N_FLOORS; i++) {
        for(int j = 0; j < N_BUTTONS; j++) {
            queue[i][j] = 0;
            elevio_buttonLamp(i,j,0);
        }
    }
}
void add_order() {
    for(int i = 0; i < N_FLOORS; i++) {
        for(int j = 0; j < N_BUTTONS; j++) {
            int btnPressed = elevio_callButton(i,j);
            if(btnPressed) {
                queue[i][j] = btnPressed;
                elevio_buttonLamp(i,j,1);
            }
        }
    }
}

void pop_order(int floorindex, int buttonindex) {
    queue[floorindex][buttonindex] = 0;
}

int queue_is_empty() {
    for(int i = 0; i < N_FLOORS; i++) {
        for(int j = 0; j < N_BUTTONS; j++) {
            if(queue[i][j] == 1) {
                return 0;
            }
        }
    }
    return 1;
}

int queue_find_floor() {
    for(int i = 0; i < N_FLOORS; i++) {
        for(int j = 0; j < N_BUTTONS; j++) {
            if(queue[i][j] == 1) {
                return i;
            }
        }
    }
    return 0;
}

void clear_floor(int floor) {
    for(int i = 0; i < N_BUTTONS; i++) {
        queue[floor][i] = 0;
        elevio_buttonLamp(floor, i, 0);
    }
}
