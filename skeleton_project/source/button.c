#include "button.h"

int read_stop_button_signal() {
    return elevio_stopButton();
}
ButtonState getStopButtonState(StopButton* stopbutton) {
    return stopbutton -> state;
}

//hei