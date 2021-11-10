#include <stdio.h>
#include <stdlib.h>
#include "stack.h"
#include "claim.h"

Stack* newStack()
{
  Stack *s = malloc(sizeof(Stack));
  s->head = NULL;
  return s;
}

Node* newNode(Node *data)
{
  Node* n = malloc(sizeof(Node));

  n->level = data->level;
  n->type = data->type;
  n->next = NULL;

  return n;
}

void push(Stack* s, void* data)
{
  Node* n = newNode(data);
  n->next = s->head;
  s->head = n;
}

void* pop(Stack* s)
{
  if(s->head == NULL)
    return NULL;

  Node* toDel = s->head;
  Node* toRet = s->head;
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