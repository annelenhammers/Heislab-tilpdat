#pragma once
#include "../driver/elevator_cab.h"


typedef enum {
    UP = 1,
    DOWN = -1,
    IDLE = 0
}QueueDirection;


typedef struct {

    QueueDirection queue_direction;
    Floor floor;
    QueueState* prev;
    QueueState* next;              

}QueueState;


typedef struct {

    int size;
    QueueState* head;
    QueueState* tail;
    
}Queue;

QueueState* queue_state_constructor(QueueDirection queuedirection, Floor floor);
void queue_state_destroy(QueueState* queuestate);
void queue_destroy(Queue* queue);
void queue_clear(Queue* queue);
bool queue_empty(Queue* queue);
QueueState* queue_pop(Queue* queue);
void AddToQueue(Queue* queue, QueueState* queuestate);
void initialize_queuestate(QueueDirection dir, Floor floor, QueueState* prev);






