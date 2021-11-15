#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "claim.h"
#include "stack.h"

Stack *newDeck()
{
    char list[52][2] = {{'0' , 'G'}, {'0' , 'G'}, {'0' , 'G'}, {'0' , 'G'}, {'0' , 'G'},
                        {'1' , 'G'}, {'2' , 'G'}, {'3' , 'G'}, {'4' , 'G'}, {'5' , 'G'}, 
                        {'6' , 'G'}, {'7' , 'G'}, {'8', 'G'}, {'9', 'G'},

                        {'0' , 'E'}, {'1' , 'E'}, {'2' , 'E'}, {'3' , 'E'}, {'4' , 'E'}, 
                        {'5' , 'E'}, {'6' , 'E'}, {'7' , 'E'}, {'8' , 'E'}, {'9' , 'E'},

                        {'0' , 'N'}, {'1' , 'N'}, {'2' , 'N'}, {'3' , 'N'}, {'4' , 'N'}, 
                        {'5' , 'N'}, {'6' , 'N'}, {'7' , 'N'}, {'8' , 'N'}, {'9' , 'N'},

                        {'0' , 'D'}, {'1' , 'D'}, {'2' , 'D'}, {'3' , 'D'}, {'4' , 'D'}, 
                        {'5' , 'D'}, {'6' , 'D'}, {'7' , 'D'}, {'8' , 'D'}, {'9' , 'D'},

                        {'2' , 'K'}, {'3' , 'K'}, {'4' , 'K'}, {'5' , 'K'}, {'6' , 'K'},
                        {'7' , 'K'}, {'8' , 'K'}, {'9' , 'K'},

                        };

    int i;
    int j;
    int b = 0;
    int n = 52;
    int r;
    srand(time(NULL));

    char temp[52][2];
    int repeated[52];

    for(i = 0 ; i < 52 ; i++)
    {
        r = rand() % n;
        for(j = 0 ; j < i ; j++)
        {
            if(repeated[j] == r)
            {
                b = 1;
                break;
            }
        }

        if(b == 0)
        {
            temp[i][0] = list[r][0];
            temp[i][1] = list[r][1];
            repeated[i] = r;
        }
        else
        {
            b = 0;
            i--;
        }

    }

    Stack *D = newStack();
    int e;

    D->cN = 0;
    
    Node *focusNode;

    for(i = 0 ; i < 52 ; i++)
    {
        if(D->cN == 0)
        {
            D->head = malloc(sizeof(Node));
            e = (int*)temp[i][0];

            D->head->level = e - 48;
            D->head->type = temp[i][1];
            D->head->next = NULL;

            focusNode = D->head;
        }
        else
        {
            focusNode->next = malloc(sizeof(Node));
            focusNode = focusNode->next;

            e = (int*)temp[i][0];

            focusNode->level = e - 48;
            focusNode->type = temp[i][1];
            focusNode->next = NULL;
        }

        D->cN++;

        //printf("#%d Type: %c with level: %d\n", D->cN, focusNode->type, focusNode->level);
    }

    return D;    

}

Stack *newPlayer(Stack *D)
{
    Stack *p = newStack();

    int i;
    Node *temp;
    for(i = 0 ; i < 13 ; i++)
    {
        temp = pop(D);
        push(p, temp);

        D->cN--;
        p->cN++;
    }

    return p;
}

void firstR(Stack *D, Stack *V, Stack *P1, Stack *P2, Stack *P1R2, Stack *P2R2)
{
    Stack *temp = newStack();
    Node *tC = pop(D);
    Node *nT;
    Node *nT2;
    Node *r;
    int c;
    int i;

    printf("[Deck] Type: %c level: %d\n", tC->type, tC->level);

    if(D->t == 0)
    {
        displayD(P1);
        printf("Introduce nUm de carta: ");
        scanf("%d", &c);
        for(i = 0 ; i < c ; i++)
        {
            r = pop(P1);
            push(temp, r);
        }
        
        nT = pop(temp);

        while(peek(temp) != NULL)
        {
            r = pop(temp);
            push(P1, r);
        }

        displayD(P2);
        printf("Introduce nUm de carta: ");
        scanf("%d", &c);
        for(i = 0 ; i < c ; i++)
        {
            r = pop(P2);
            push(temp, r);
        }
        
        nT2 = pop(temp);

        while(peek(temp) != NULL)
        {
            r = pop(temp);
            push(P2, r);
        }
        
    }

    printf("[Deck] Type: %c level: %d\n", tC->type, tC->level);
    printf("[P1] Type: %c level: %d\n", nT->type, nT->level);
    printf("[P2] Type: %c level: %d\n", nT2->type, nT2->level);
}

void displayD(Stack * D)
{
    Node *focusNode = D->head;
    int i = 1;

    while(focusNode != NULL)
    {
        printf("#%d Type: %c with level: %d\n", i, focusNode->type, focusNode->level);
        focusNode = focusNode->next;
        i++;
    }

    printf("\n\n");
}