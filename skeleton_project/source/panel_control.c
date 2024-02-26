//denne modulen inneholder etasjepanelet (floorpanel) sin funksjonalitet, 
//i tillegg til oppdatering av button og lights for hvert floor

#include "../source/driver/elevio.h"

//Kommentar
//det burde sikkert ikke være vanlig int


//FLOOR PANEL

int floor_button_up[N_FLOORS] = {0};
int floor_button_down[N_FLOORS] = {0};
int floor_lights[N_FLOORS] = {0};

void init_floor(){}
void update_floor_button(){}
void update_floor_lights(){}

//ELEVATOR PANEL

int elevator_buttons[N_FLOORS] = {0};

//update elevator button function

