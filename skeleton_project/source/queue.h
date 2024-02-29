#pragma once
#include "driver/elevator_cab.h"



typedef enum {
    UP = 1,
    DOWN = -1,
    IDLE = 0
}QueueDirection;

typedef struct{
    QueueDirection queuedirection;
    Floor floor;
    QueueState* prev;
    QueueState* next;
}QueueState;

typedef struct {
    int size;
    QueueState* head;
    QueueState* tail;
}Queue;

QueueState* queuestateconstructor(QueueDirection queuedirection, Floor floor);
void DestoryQueueState(QueueState* queuestate);
void DestoryQueue(Queue* queue);
void clearQueue(Queue* queue);
bool EmptyQueue(Queue* queue);
QueueState* PopQueue(Queue* queue);
void AddToQueue(Queue* queue, QueueState* queuestate);
void initialize_queuestate(QueueDirection dir, Floor floor, QueueState* prev);






