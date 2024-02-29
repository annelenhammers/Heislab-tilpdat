#include "panels.h"

Floor_Panel* floor_panel_constructor(ButtonState floor_one_up, ButtonState floor_two_up, ButtonState floor_three_up, ButtonState floor_two_down, ButtonState floor_three_down, ButtonState floor_four_down,bool lamp_one, bool lamp_two, bool lamp_three, bool lamp_four) {
    Floor_Panel* floor_panel = (Floor_Panel*)malloc(sizeof(Floor_Panel));

    floor_panel -> floor_one_up = floor_one_up;
    floor_panel -> floor_two_up = floor_two_up;
    floor_panel -> floor_three_up = floor_three_up;

    floor_panel -> floor_two_down = floor_two_down;
    floor_panel -> floor_three_down = floor_three_down;
    floor_panel -> floor_four_down = floor_four_down;

    elevio_buttonLamp(0, BUTTON_HALL_UP, floor_one_up);
    elevio_buttonLamp(1, BUTTON_HALL_UP, floor_two_up);
    elevio_buttonLamp(2, BUTTON_HALL_UP, floor_three_up);

    elevio_buttonLamp(1, BUTTON_HALL_DOWN, floor_two_down);
    elevio_buttonLamp(2, BUTTON_HALL_DOWN, floor_three_down);
    elevio_buttonLamp(3, BUTTON_HALL_DOWN, floor_four_down);

    update_lamp_one(floor_panel, false);
    update_lamp_two(floor_panel, false);
    update_lamp_three(floor_panel, false);
    update_lamp_four(floor_panel, false);
}

//Konstruktør kalles for å initialisere

Elevator_panel* elevator_panel_constructor(ButtonState first_floor, ButtonState second_floor, ButtonState third_floor, ButtonState fourth_floor, ButtonState door_open, ButtonState stop_button, bool obstruction) {
    Elevator_panel* elevator_panel = (Elevator_panel*)malloc(sizeof(Elevator_panel));

    elevator_panel -> first_floor = first_floor;
    elevator_panel -> second_floor = second_floor;
    elevator_panel -> third_floor = third_floor;
    elevator_panel -> fourth_floor = third_floor;
    elevator_panel -> stop_button = stop_button;
    elevator_panel -> obstruction = obstruction;

    elevio_buttonLamp(0, BUTTON_CAB, first_floor);
    elevio_buttonLamp(1, BUTTON_CAB, second_floor);
    elevio_buttonLamp(2, BUTTON_CAB, third_floor);
    elevio_buttonLamp(3, BUTTON_CAB, fourth_floor);

}


void update_floor_one(Elevator_panel* elevator_panel, ButtonState floor_one) {
    if(elevator_panel -> first_floor != floor_one) {
        elevator_panel -> first_floor = floor_one;
        elevio_buttonLamp(0, BUTTON_CAB, floor_one);
    }
}

void update_floor_two(Elevator_panel* elevator_panel, ButtonState floor_two) {
    if(elevator_panel -> second_floor != floor_two) {
        elevator_panel -> second_floor = floor_two;
        elevio_buttonLamp(1, BUTTON_CAB, floor_two);
    }
}

void update_floor_three(Elevator_panel* elevator_panel, ButtonState floor_three) {
    if(elevator_panel -> third_floor != floor_three) {
        elevator_panel -> third_floor = floor_three;
        elevio_buttonLamp(1, BUTTON_CAB, floor_three);
    }
}

void update_floor_four(Elevator_panel* elevator_panel, ButtonState floor_four) {
    if(elevator_panel -> fourth_floor != floor_four) {
            elevator_panel -> fourth_floor = floor_four;
            elevio_buttonLamp(1, BUTTON_CAB, floor_four);
        }
    }

void update_stop_button(Elevator_panel* elevator_panel, ButtonState stop_button) {
    if(elevator_panel -> stop_button != stop_button) {
        elevator_panel -> stop_button = stop_button;
        elevio_stopLamp(stop_button);
    }

}
void update_obstruction(Elevator_panel* elevator_panel, int obstruction) {
if(elevator_panel -> obstruction != obstruction) {
        elevator_panel -> obstruction = obstruction;
    }
}

ButtonState get_stop_button_state(Elevator_panel* elevator_panel) {
    return elevator_panel -> stop_button;
}


void update_floor_one_up(Floor_Panel* floor_panel, ButtonState buttonstate) {
    if(floor_panel -> floor_one_up != buttonstate) {
            floor_panel -> floor_one_up = buttonstate;
            elevio_buttonLamp(0, BUTTON_HALL_UP, buttonstate);
        }
}


void update_floor_two_up(Floor_Panel* floor_panel, ButtonState buttonstate) {
    if(floor_panel -> floor_two_up != buttonstate) {
            floor_panel -> floor_two_up = buttonstate;
            elevio_buttonLamp(1, BUTTON_HALL_UP, buttonstate);
        }
}
void update_floor_three_up(Floor_Panel* floor_panel, ButtonState buttonstate) {
    if(floor_panel -> floor_three_up != buttonstate) {
            floor_panel -> floor_three_up = buttonstate;
            elevio_buttonLamp(2, BUTTON_HALL_UP, buttonstate);
        }
}

void update_floor_two_down(Floor_Panel* floor_panel, ButtonState buttonstate) {
    if(floor_panel -> floor_two_down != buttonstate) {
            floor_panel -> floor_two_down = buttonstate;
            elevio_buttonLamp(1, BUTTON_HALL_DOWN, buttonstate);
        }
}
void update_floor_three_down(Floor_Panel* floor_panel, ButtonState buttonstate) {
    if(floor_panel -> floor_three_down != buttonstate) {
            floor_panel -> floor_three_down = buttonstate;
            elevio_buttonLamp(2, BUTTON_HALL_DOWN, buttonstate);
        }
}
void update_floor_four_down(Floor_Panel* floor_panel, ButtonState buttonstate) {
    if(floor_panel -> floor_four_down != buttonstate) {
            floor_panel -> floor_four_down = buttonstate;
            elevio_buttonLamp(3, BUTTON_HALL_DOWN, buttonstate);
        }
}

void update_lamp_one(Floor_Panel* floor_panel, bool light) {
    if(floor_panel -> lamp_one != light) {
            floor_panel -> lamp_one = light;
            elevio_floorIndicator(0);
        }
}
void update_lamp_two(Floor_Panel* floor_panel, bool light) {
    if(floor_panel -> lamp_two != light) {
            floor_panel -> lamp_two = light;
            elevio_floorIndicator(1);
        }

}
void update_lamp_three(Floor_Panel* floor_panel, bool light) {
    if(floor_panel -> lamp_three != light) {
            floor_panel -> lamp_three = light;
            elevio_floorIndicator(2);
        }
}
void update_lamp_four(Floor_Panel* floor_panel, bool light) {
    if(floor_panel -> lamp_four != light) {
            floor_panel -> lamp_four = light;
            elevio_floorIndicator(3);
        }
}

void initialize_floor_panel(Floor_Panel* floor_panel) {
    Floor_Panel* fl = floor_panel_constructor(UNPRESSED, UNPRESSED, UNPRESSED, UNPRESSED, UNPRESSED, UNPRESSED, false, false, false, false);  
}
void initialize_elevator_panel(Elevator_panel* elevator_panel) {
    Elevator_panel* el = elevator_panel_constructor(UNPRESSED, UNPRESSED, UNPRESSED, UNPRESSED, UNPRESSED, UNPRESSED, false); 
}


