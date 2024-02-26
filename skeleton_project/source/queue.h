#pragma once
#include "floor.h"


typedef enum {
    UP = 0,
    DOWN = 1,

}QueueDirection;

typedef struct{
    QueueDirection queuedirection;
    Floor floor;
    QueueState* prevoius;
}QueueState;

typedef struct {
    int size;
    QueueState* prevoius;
    QueueState* head;
    QueueState* tail;
    QueueState* next;
}Queue;

QueueState* queuestate(QueueDirection queuedirection, Floor floor);
void DestoryQueue(Queue* queue);
void clearQueue(Queue* queue);

