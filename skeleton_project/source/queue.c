#include "queue.h"
#include <stddef.h>
#include <stdbool.h>

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

void update_queue_init(){

    update_queue[0][BUTTON_HALL_UP] = update_floor_one_up;
    update_queue[1][BUTTON_HALL_UP] = update_floor_two_up;
    update_queue[2][BUTTON_HALL_UP] = update_floor_three_up;

    update_queue[1][BUTTON_HALL_DOWN] = update_floor_two_down;
    update_queue[2][BUTTON_HALL_DOWN] = update_floor_three_down;
    update_queue[3][BUTTON_HALL_DOWN] = update_floor_four_down;

    update_queue[0][BUTTON_CAB] = update_lamp_one;
    update_queue[1][BUTTON_CAB] = update_lamp_two;
    update_queue[2][BUTTON_CAB] = update_lamp_three;
    update_queue[3][BUTTON_CAB] = update_lamp_four;
}

int queue_fix_orders(Queue** head, QueueState* new_order) {
    if (new_order == NULL) {
        return 1;
    }
    new_order -> next = *head;
    if (*head != NULL){
        (*head) -> previous = new_order;
    }

    *head = new_order;
    new_order -> previous = NULL;

    queue_size++;

    update_queue[new_order -> floor][new_order -> queue_direction](new_order -> button_state);

    return 0;
}

