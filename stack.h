#ifndef STACK_STACK_H
#define STACK_STACK_H

typedef void* TYPE;

typedef struct node Node;

typedef struct stack Stack;

Stack* newStack();
void push(Stack *stack, void *value);
void *pop(Stack *stack);
void *peek(Stack *stack);
void display(Stack *stack);

int compare(void *a, void *b);
void sortStack(Stack *s, int(*compare)(void *a, void *b));

#endif