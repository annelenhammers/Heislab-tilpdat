#include "queue.h"
#include <stddef.h>

QueueState* Queuestate(QueueDirection queuedirection, Floor floor){
    QueueState* questate = (QueueState*)malloc(sizeof(QueueState));
    questate -> floor = floor;
    questate -> queuedirection = queuedirection;
    questate -> prevoius = NULL;
    return questate;
}

void DestoryQueue(Queue* queue) {
    free(queue);
}
void clearQueue(Queue* queue) {
    
}
