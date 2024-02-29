#pragma once
#include "driver/elevator_cab.h"



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

QueueState* queuestateconstructor(QueueDirection queuedirection, Floor floor);
void DestoryQueueState(QueueState* queuestate);
void DestoryQueue(Queue* queue);
void clearQueue(Queue* queue);
bool EmptyQueue(Queue* queue);
QueueState* PopQueue(Queue* queue);
void AddToQueue(Queue* queue, QueueState* queuestate);





