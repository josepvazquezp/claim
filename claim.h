#ifndef CLAIM_CLAIM_H
#define CLAIM_CLAIM_H

struct node
{
    int level;
    char type;
    //imagen
    struct node *next;
};

typedef struct node Node;

struct stack
{
    Node *head;
    int cN;
};

typedef struct stack Stack;

Stack *newDeck();
Stack *newPlayer(Stack *D);

void firstR(Stack *P1, Stack *P2);

void displayD(Stack * D);

#endif