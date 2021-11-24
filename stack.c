#include <stdio.h>
#include <stdlib.h>
#include "stack.h"
#include "claim.h"

Stack* newStack()
{
    Stack *s = malloc(sizeof(Stack));
    s->head = NULL;
    s->t = 0;
    return s;
}

// Node* newNode(Node *data)
// {
//   Node* n = malloc(sizeof(Node));

//   n->level = data->level;
//   n->type = data->type;
//   n->next = NULL;

//   return n;
// }

void push(Stack* s, Node* data)
{
    if(s->head == NULL)
    {
        s->head = malloc(sizeof(Node));
        s->head->level = data->level;
        s->head->type = data->type;
        s->head->next = NULL;
        return;
    }

    Node* n = malloc(sizeof(Node));
    n->level = data->level;
    n->type = data->type;
    n->next = s->head;
    s->head = n;

}

void* pop(Stack* s)
{
    if(s->head == NULL)
        return NULL;

    Node* toDel = s->head;
    Node* toRet = malloc(sizeof(Node));
    toRet->level = s->head->level;
    toRet->type = s->head->type;
    s->head = s->head->next;
    free(toDel);

    return toRet;
}

void* peek(Stack* s)
{
    if(s->head == NULL)
        return NULL;
    return s->head;
}