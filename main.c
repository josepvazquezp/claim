#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "claim.h"
#include "stack.h"

int main(void)
{
    Stack *D = newDeck();
    //Stack *P1 = newPlayer(D);
    //Stack *P2 = newPlayer(D);

    //displayD(P1);
    //displayD(P2);

    displayD(D);

    return 0;
}