#include "queue.h"
#include <stddef.h>

QueueState* queuestateconstructor(QueueDirection queuedirection, Floor floor){
    QueueState* questate = (QueueState*)malloc(sizeof(QueueState));
    questate -> floor = floor;
    questate -> queuedirection = queuedirection;
    questate -> prev = NULL;
    return questate;
}

void DestoryQueueState(QueueState* queuestate) {
    free(queuestate);
}

void DestoryQueue(Queue* queue) {
    clearQueue(queue);
    free(queue);
}

void clearQueue(Queue* queue) {
    while(EmptyQueue(queue) != true) {
        QueueState* queuestate = PopQueue(queue);
        DestoryQueue(queuestate);
    }
}

bool EmptyQueue(Queue* queue) {
    return queue -> size == 0;
}
QueueState* PopQueue(Queue* queue) {
    QueueState* state;

    if(EmptyQueue(queue) == true) {
        return NULL;
    }
    else {
    state = queue -> head;
    queue -> head = queue -> head -> prev;
    queue -> size--;

    return state;
    }
}

void AddToQueue(Queue* queue, QueueState* queuestate) {
    queuestate -> prev = NULL;
    if(queue -> size == 0) {
        queue -> tail = queuestate;
        queue -> head = queuestate;
    }
    else {
        queue -> tail -> prev = queuestate;
        queue -> tail = queuestate;
    }
    queue -> size++;
}

void initialize_queuestate(QueueDirection dir, Floor floor, QueueState* prev) {
    if(elevio_floorIndicator > 0) {
        queuestateconstructor(DOWN, FIRST_FLOOR);
    }
    else {
        queuestateconstructor(IDLE, FIRST_FLOOR);
    }
    
}


