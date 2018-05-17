#include "Queue.h"

void append(Queue* q, Node* n){
   q->tail->next =  n;
   q->tail = n;
}

Node pop(Queue* q){
    Node n = *(q->head);
    q->head = q->head->next;
    return n;
}
