#include "queue.h"
#include <stddef.h>

/*variabler som trengs:
current elevator floor?
*/

int queue_size = 0;


QueueState* queue_state_constructor(QueueDirection queue_direction, Floor floor) {
    
    QueueState* queue_state = (QueueState*)malloc(sizeof(QueueState));
    
    queue_state -> floor = floor;
    queue_state -> queue_direction = queue_direction;
    queue_state -> previous = NULL;
    
    return queue_state;
}

Queue* queue_init() {
    
    Queue* queue = (Queue*)malloc(sizeof(Queue));
    
    queue -> size = 0;
    queue -> previous = NULL;
    queue -> head = NULL;
    queue -> tail = NULL;
    queue -> next = NULL;

    return queue;
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
    } else {
    state = queue -> head;
    queue -> head = queue -> head -> previous;
    queue -> size--;

    return state;
    }
}

void queue_add(Queue* queue, QueueState* queue_state) {
    
    queue -> previous = NULL;

    if(queue -> size == 0) {
        queue -> tail = queue_state;
        queue -> head = queue_state;
    } else {
        queue -> tail -> previous = queue_state;
        queue -> tail = queue_state;
    }

    queue -> size++;
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

