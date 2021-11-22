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

    while(peek(D) != NULL)
    {
        itsGoTimeBBY(D, V1, V2, P1, P2, P1R2, P2R2);
    }

    int i = 1;

    while(peek(P1R2) != NULL && peek(P2R2) != NULL)
    {
        printf("\t\tRONDA 2\n \t\tvuelta: %d\n", i);
        round2(D, V1, V2, P1R2, P2R2);
        printf("\n\n");
        printf("\t\tVOTANTES P1\n");
        displayD(V1);
        printf("-------\n\n");
        printf("\t\tVOTANTES P2\n");
        displayD(V2);
        printf("\n\n");
        i++;
    }
    
    claimWinner(V1, V2);

    return 0;
}