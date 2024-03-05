#pragma once

#include "driver/elevator_cab.h"

int queue[N_FLOORS][N_FLOORS];
void queue_initializer();
void add_order();
void pop_order(int floorindex, int buttonindex);
int queue_is_empty();

int queue_find_floor();
void clear_floor(int floor);



