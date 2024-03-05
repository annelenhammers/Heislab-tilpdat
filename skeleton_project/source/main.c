#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include "driver/elevio.h"
#include "driver/elevator_cab.h"




int main(){
    elevio_init();
    queue_initializer();
    Elevator_cab* cab = elevator_cab(INIT, DIRN_STOP, DIRN_STOP, 0);
    intialize_elevator_cab(&cab);

    
    while(1){
        
        run(cab);
        if(INACTIVE) {
            break;
        }

    }        

    return 0;
}
