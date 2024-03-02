#pragma once
#include "driver/elevio.h"

typedef struct {
    ButtonType button_type;
    int floor;
} Call;
Call* calls;