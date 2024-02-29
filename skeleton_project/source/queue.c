#include "queue.h"
#include <stddef.h>

QueueState* queue_state_constructor(QueueDirection queuedirection, Floor floor){
    QueueState* questate = (QueueState*)malloc(sizeof(QueueState));
    questate -> floor = floor;
    questate -> queue_direction = queuedirection;
    questate -> prev = NULL;
    return questate;
}


void queue_state_destroy(QueueState* queue_state) {
    free(queue_state);
}

void queue_destroy(Queue* queue) {
    queue_clear(queue);
    free(queue);
}

void queue_clear(Queue* queue) {
    
    while(queue_empty(queue) != true) {
        QueueState* queue_state = queue_pop(queue);
        queue_destroy(queue_state);
    } 
}

bool queue_empty(Queue* queue) {
    return queue -> size == 0;
}

QueueState* queue_pop(Queue* queue) {
   
    QueueState* state;

    if(queue_empty(queue) == true) {
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

QueueState* queue_latest_order(Queue* queue) {
    return queue -> tail;
}

QueueState* queue_order(Queue* queue, int order_position) {
    QueueState* state_of_order = queue -> head;
    for (int i = 0; i < order_position && state_of_order != NULL; i++) {
        state_of_order = state_of_order -> next;
    }
    return state_of_order;
}   

