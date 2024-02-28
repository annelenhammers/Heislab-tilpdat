#pragma once
#include "elevator_cab.h"

typedef enum {

    PRESSED = 1,
    UNPRESSED = 0

}ButtonState;


typedef struct {

    ButtonState first_floor;
    ButtonState second_floor;
    ButtonState third_floor;
    ButtonState fourth_floor;
    ButtonState stop_button;
    ButtonState door_open;
    bool obstruction;

}Elevator_panel;

typedef struct {

    bool floor_one_up;
    bool floor_two_up;
    bool floor_three_up;
    
    bool floor_two_down;
    bool floor_three_down;
    bool floor_four_down;

}Floor_Panel;


