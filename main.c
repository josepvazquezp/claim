#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "claim.h"
#include "stack.h"

int main(void)
{
    //setbuff(stdout, 0);

    Stack *V1 = newStack();
    Stack *V2 = newStack();
    Stack *D = newDeck();
    //displayD(D);

    Stack *P1 = newPlayer(D);
    //displayD(P1);

    Stack *P2 = newPlayer(D);
    //displayD(P2);

    //displayD(D);

    Stack *P1R2 = newStack();
    Stack *P2R2 = newStack();

    itsGoTimeBBY(D, V1, V2, P1, P2, P1R2, P2R2);
    

    return 0;
}