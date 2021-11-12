#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "claim.h"
#include "stack.h"

int main(void)
{
    Stack *D = newDeck();
    displayD(D);

    Stack *P1 = newPlayer(D);
    displayD(P1);

    //Stack *P2 = newPlayer(D);
    //displayD(P2);

    //displayD(D);

    return 0;
}