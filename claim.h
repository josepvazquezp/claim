#ifndef CLAIM_CLAIM_H
#define CLAIM_CLAIM_H

struct Cart
{
    int level;
    char type;
    //imagen
    struct cart *next;
};

typedef struct Cart cart;

struct Deck
{
    cart *top;
    int cN;
};

typedef struct Deck deck;

deck *newGame();


#endif