#pragma once
#include "driver/elevator_cab.h"
#include "panels.h"
#include "driver/elevio.h"


typedef enum {
    UP = 1,
    DOWN = -1,
    IDLE = 0
}QueueDirection;


typedef struct {

    QueueDirection queue_direction;
    Floor floor;

    ButtonState button_state;
    void* new_order;             
    void* prev;
    void* next;              


}QueueState;


typedef struct {

    int size;
    QueueState* head;
    QueueState* tail;
    
}Queue;

QueueState* queue_state_constructor(QueueDirection queue_direction, Floor floor);
void queue_state_destroy(QueueState* queue_state);
void queue_destroy(Queue* queue);
void queue_clear(Queue* queue);
bool queue_empty(Queue* queue);
QueueState* queue_pop(Queue* queue);
void AddToQueue(Queue* queue, QueueState* queue_state);
void initialize_queuestate(QueueDirection dir, Floor floor, QueueState* prev);


typedef void (*UpdateQueueOfOrders)(ButtonState);
UpdateQueueOfOrders update_queue[N_FLOORS][N_BUTTONS];
void update_queue_init();
QueueState* queue_latest_order(Queue* queue);
QueueState* queue_order(Queue* queue, int order_position);

