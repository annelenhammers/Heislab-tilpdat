#include "queue.h"
#include <stddef.h>

QueueState* queuestateconstructor(QueueDirection queuedirection, Floor floor){
    QueueState* questate = (QueueState*)malloc(sizeof(QueueState));
    questate -> floor = floor;
    questate -> queuedirection = queuedirection;
    questate -> prevoius = NULL;
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
    queue -> head = queue -> head -> prevoius;
    queue -> size--;

    return state;
    }
}

void AddToQueue(Queue* queue, QueueState* queuestate) {
    queue -> prevoius = NULL;
    if(queue -> size == 0) {
        queue -> tail = queuestate;
        queue -> head = queuestate;
    }
    else {
        queue -> tail -> prevoius = queuestate;
        queue -> tail = queuestate;
    }
    queue -> size++;

}


