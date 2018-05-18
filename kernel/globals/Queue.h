#ifndef QUEUE_H
#define QUEUE_H
#include <stdint.h>

typedef struct Node{
    uintptr_t value;
    struct Node* next;
}Node;

typedef struct {
    Node* head;
    Node* tail;
}Queue;

void append(Queue*, Node*);
Node pop(Queue*);
#endif //QUEUE_H
