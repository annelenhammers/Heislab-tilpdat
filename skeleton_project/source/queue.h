#pragma once
#include "../driver/elevator_cab.h"
#include "panels.h"
#include "elevio.h"


typedef enum {
    UP = 0,
    DOWN = 1,
} QueueDirection;


typedef struct {

    QueueDirection queue_direction;
    Floor floor;
    ButtonState button_state;
    QueueState* previous;
    QueueState* next; 
    QueueState* new_order;             

} QueueState;


typedef struct {

    int size;

    QueueState* previous;
    QueueState* head;
    QueueState* tail;
    QueueState* next;

} Queue;


typedef struct {

    int direction_of_current_order;
    int direction_of_next_order;
    int floor_of_current_order;
    int floor_of_next_order;

} StateMachineUtils;


QueueState* queue_state_constructor(QueueDirection queue_direction, Floor floor);
void queue_state_destroy(QueueState* queue_state);
void queue_destroy(Queue* queue);
void queue_clear(Queue* queue);
bool queue_empty(Queue* queue);
QueueState* queue_pop(Queue* queue);
void queue_add(Queue* queue, QueueState* queue_state);

typedef void (*UpdateQueueOfOrders)(ButtonState);
UpdateQueueOfOrders update_queue[N_FLOORS][N_BUTTONS];
void update_queue_init();
QueueState* queue_latest_order(Queue* queue);
QueueState* queue_order(Queue* queue, int order_position);

