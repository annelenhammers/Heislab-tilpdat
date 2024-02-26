#pragma once

typedef enum {
    PRESSED = 1,
    UNPRESSED = 0
}ButtonState;

typedef struct {
    ButtonState state;
}StopButton;

int read_stop_button_signal();
ButtonState getStopButtonState(StopButton* stopbutton);
void stopbuttonpressed();

