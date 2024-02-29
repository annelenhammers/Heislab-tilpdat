#pragma once
#include "elevator_cab.h"

typedef enum {

    DEPRESSED = 1,
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

    ButtonState floor_one_up;
    ButtonState floor_two_up;
    ButtonState floor_three_up;
    
    ButtonState floor_two_down;
    ButtonState floor_three_down;
    ButtonState floor_four_down;

    ButtonState lamp_one;
    ButtonState lamp_two;
    ButtonState lamp_three;
    ButtonState lamp_four;


}Floor_Panel;

Floor_Panel* floor_panel_constructor(ButtonState floor_one_up, 
                                        ButtonState floor_two_up, 
                                        ButtonState floor_three_up, 
                                        ButtonState floor_two_down, 
                                        ButtonState floor_three_down, 
                                        ButtonState floor_four_down);

Elevator_panel* elevator_panel_constructor(ButtonState first_floor, 
                                            ButtonState second_floor, 
                                            ButtonState third_floor, 
                                            ButtonState fourth_floor, 
                                            ButtonState door_open, 
                                            ButtonState stop_button, 
                                            bool obstruction);


void update_floor_one(Elevator_panel* elevator_panel, ButtonState floor_one);
void update_floor_two(Elevator_panel* elevator_panel, ButtonState floor_two);
void update_floor_three(Elevator_panel* elevator_panel, ButtonState floor_three);
void update_floor_four(Elevator_panel* elevator_panel, ButtonState floor_four);
void update_stop_button(Elevator_panel* elevator_panel, ButtonState stop_button);
void update_obstruction(Elevator_panel* elevator_panel, int obstruction);
ButtonState get_stop_button_state(Elevator_panel* elevator_panel);

void update_floor_one_up(Floor_Panel* floor_panel, ButtonState buttonstate);
void update_floor_two_up(Floor_Panel* floor_panel, ButtonState buttonstate);
void update_floor_three_up(Floor_Panel* floor_panel, ButtonState buttonstate);

void update_floor_two_down(Floor_Panel* floor_panel, ButtonState buttonstate);
void update_floor_three_down(Floor_Panel* floor_panel, ButtonState buttonstate);
void update_floor_four_down(Floor_Panel* floor_panel, ButtonState buttonstate);

void update_lamp_one(Floor_Panel* floor_panel, ButtonState buttonstate);
void update_lamp_two(Floor_Panel* floor_panel, ButtonState buttonstate);
void update_lamp_three(Floor_Panel* floor_panel, ButtonState buttonstate);
void update_lamp_four(Floor_Panel* floor_panel, ButtonState buttonstate);




