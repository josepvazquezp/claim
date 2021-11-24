#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "claim.h"
#include "stack.h"
#include "raylib.h"

void drawStart()
{
    Color backGround = {23, 32, 42, 255};
    Color textStart = {219, 182,0, 255};
    ClearBackground(backGround);
    DrawText("Claim", 500, 250, 250, WHITE);
    DrawText("Press enter to START", 450, 600, 60, textStart);
}

void drawTable()
{
    Image backG= LoadImage("C:\\Users\\Jose\\Documents\\ITESO\\Semestre3\\Programacion con memoria dinamica\\claim_Clion\\cards\\Tablero.png");
    Texture2D textureBack = LoadTextureFromImage(backG);
    UnloadImage(backG);
    DrawTexture(textureBack, 0, 0, WHITE);

    int i;
    int ac = 5;
    for(i = 0 ; i < 10 ; i++)
    {
        DrawRectangle(ac, 10, 131, 198, WHITE);
        DrawRectangle(ac, 690, 131, 198, WHITE);
        ac += 160;
    }
    for(i = 0, ac = 5 ; i < 3 ; i++)
    {
        DrawRectangle(ac, 220, 131, 198, WHITE);
        DrawRectangle(ac, 480, 131, 198, WHITE);
        ac += 160;
    }

    Image deckCard = LoadImage("C:\\Users\\Jose\\Documents\\ITESO\\Semestre3\\Programacion con memoria dinamica\\claim_Clion\\cards\\G0.png");
    ImageRotateCW(&deckCard);
    Texture2D textureDeck = LoadTextureFromImage(deckCard);
    UnloadImage(deckCard);

    DrawRectangle(1390, 382, 202, 135, WHITE);
    DrawTexture(textureDeck, 1392, 384, WHITE);

}

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

    char root[98] = "C:\\Users\\Jose\\Documents\\ITESO\\Semestre3\\Programacion con memoria dinamica\\claim_Clion\\cards\\G0.png";
    Image iTemp;
    Texture2D tTemp;

    for(i = 0 ; i < 52 ; i++)
    {
        if(D->cN == 0)
        {
            D->head = malloc(sizeof(Node));
            e = (int*)temp[i][0];

            D->head->level = e - 48;
            D->head->type = temp[i][1];
            D->head->next = NULL;

            root[92] = temp[i][1];
            root[93] = temp[i][0];

            D->head->card = LoadImage(root);

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

            root[92] = temp[i][1];
            root[93] = temp[i][0];

            focusNode->card = LoadImage(root);
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

void itsGoTimeBBY(Stack *D, Stack *V1, Stack *V2, Stack *P1, Stack *P2, Stack *P1R2, Stack *P2R2)
{

    Stack *temp = newStack();
    Node *tC = pop(D);
    Node *nT;
    Node *nT2;
    Node *r;
    int c;
    int i;

    //printf("[Deck] Type: %c level: %d\n\n", tC->type, tC->level);

    if(D->t == 0)
    {
        //displayD(P1);
        //printf("[P1] Introduce nUm de carta: ");
        //scanf("%d", &c);
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
        //printf("\n\n");

        //printf("[P1] juega: %c%d\n", nT->type, nT->level);

        //displayD(P2);
        //printf("[P2] Introduce nUm de carta: ");
        //scanf("%d", &c);
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
        //printf("\n\n");
    }
    else if(D->t == 1)
    {
        //displayD(P2);
        //printf("[P2] Introduce nUm de carta: ");
        //scanf("%d", &c);
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
        //printf("\n\n");

        //printf("[P2] juega: %c%d\n", nT2->type, nT2->level);
        //displayD(P1);
        //printf("[P1] Introduce nUm de carta: ");
        //scanf("%d", &c);
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
        //printf("\n\n");
    }

    //printf("[Deck] Type: %c level: %d\n", tC->type, tC->level);
    //printf("[P1] Type: %c level: %d\n", nT->type, nT->level);
    //printf("[P2] Type: %c level: %d\n", nT2->type, nT2->level);

    if(nT->type == nT2->type || nT->type == 'D' || nT2->type == 'D') //comparacion de nivel y comodin
    {
        if(D->t == 0 && nT2->type == 'N' && nT->type == 'D')
        {
            push(V1, nT2);
            push(P1R2, tC);
            D->t = 0;
        }
        else if(D->t == 1 && nT->type == 'N' && nT2->type == 'D')
        {
            push(V2, nT);
            push(P2R2, tC);
            D->t = 1;
        }
        else if(nT->type == 'N' || nT2->type == 'N')
        {
            int b = 0;
            if(nT->type == nT2->type)
                b = 1;
            else if(D->t == 0 && nT2->type == 'D' && nT->type == 'N')
                b = 2;
            else if(D->t == 1 && nT->type == 'D' && nT2->type == 'N')
                b = 3;

            if(nT->level > nT2->level || (nT->level == nT2->level && D->t == 0))
            {
                if(b == 1)
                {
                    push(V1, nT);
                    push(V1, nT2);
                    push(P1R2, tC);
                    D->t = 0;
                }
                else if(b == 2)
                {
                    push(V1, nT);
                    push(P1R2, tC);
                    D->t = 0;
                }
                else if(b == 3)
                {
                    push(V1, nT2);
                    push(P1R2, tC);
                    D->t = 0;
                }
            }
            else if(nT->level < nT2->level || (nT->level == nT2->level && D->t == 1))
            {
                if(b == 1)
                {
                    push(V2, nT);
                    push(V2, nT2);
                    push(P2R2, tC);
                    D->t = 1;
                }
                else if(b == 2)
                {
                    push(V2, nT);
                    push(P2R2, tC);
                    D->t = 1;
                }
                else if(b == 3)
                {
                    push(V2, nT2);
                    push(P2R2, tC);
                    D->t = 1;
                }
            }
        }
        else if(D->t == 0 && nT->type == 'D' &&  nT2->type != 'D')
        {
            push(P1R2, tC);
            D->t = 0;
        }
        else if(D->t == 1 && nT2->type == 'D' &&  nT->type != 'D')
        {
            push(P2R2, tC);
            D->t = 1;
        }
        else if(nT->level > nT2->level || (nT->level == nT2->level && D->t == 0))
        {
            push(P1R2, tC);
            D->t = 0;
        }
        else if(nT->level < nT2->level || (nT->level == nT2->level && D->t == 1))
        {
            push(P2R2, tC);
            D->t = 1;
        }
    }
    else if(nT->type != nT2->type)
    {
        if(D->t == 0 && nT->type == 'N' && nT->level > nT2->level) //necromancers puntos directos
        {
            push(V1, nT);
            push(P1R2, tC);
            D->t = 0;
        }
        else if(D->t == 1 && nT2->type == 'N' && nT->level < nT2->level)
        {
            push(V2, nT);
            push(P2R2, tC);
            D->t = 1;
        }
        else if(D->t == 0 && nT2->type == 'N' && nT->level > nT2->level)
        {
            push(V1, nT2);
            push(P1R2, tC);
            D->t = 0;
        }
        else if(D->t == 1 && nT->type == 'N' && nT->level < nT2->level)
        {
            push(V2, nT);
            push(P2R2, tC);
            D->t = 1;
        }
        else if(D->t == 0 && nT->type == 'G' && nT2->type == 'K')
        {
            push(P2R2, tC);
            D->t = 1;
        }
        else if(D->t == 1 && nT->type == 'K' && nT2->type == 'G')
        {
            push(P1R2, tC);
            D->t = 0;
        }
        else if(D->t == 0)
        {
            push(P1R2, tC);
            D->t = 0;
        }
        else if(D->t == 1)
        {
            push(P2R2, tC);
            D->t = 1;
        }
    }

    if(D->t == 0)
    {
        tC = pop(D);
        push(P2R2, tC);
    }
    else if(D->t == 1)
    {
        tC = pop(D);
        push(P1R2, tC);
    }

    //displayD(P1R2);
    //displayD(V1);
    //printf("--------\n\n");
    //displayD(P2R2);
    //displayD(V2);
}

void round2(Stack *D, Stack *V1, Stack *V2,Stack *P1R2, Stack *P2R2)
{

    Stack *temp = newStack();
    Node *nT;
    Node *nT2;
    Node *r;
    int c;
    int i;

    if(D->t == 0)
    {
        //displayD(P1R2);
        //printf("[P1] Introduce nUm de carta: ");
        //scanf("%d", &c);
        for(i = 0 ; i < c ; i++)
        {
            r = pop(P1R2);
            push(temp, r);
        }

        nT = pop(temp);

        while(peek(temp) != NULL)
        {
            r = pop(temp);
            push(P1R2, r);
        }
        //printf("\n\n");

        //displayD(P2R2);
        //printf("[P2] Introduce nUm de carta: ");
        //scanf("%d", &c);
        for(i = 0 ; i < c ; i++)
        {
            r = pop(P2R2);
            push(temp, r);
        }

        nT2 = pop(temp);

        while(peek(temp) != NULL)
        {
            r = pop(temp);
            push(P2R2, r);
        }
        //printf("\n\n");
    }
    else if (D->t == 1)
    {
        //displayD(P2R2);
        //printf("[P2] Introduce nUm de carta: ");
        //scanf("%d", &c);
        for(i = 0 ; i < c ; i++)
        {
            r = pop(P2R2);
            push(temp, r);
        }

        nT2 = pop(temp);

        while(peek(temp) != NULL)
        {
            r = pop(temp);
            push(P2R2, r);
        }
        //printf("\n\n");

        //displayD(P1R2);
        //printf("[P1] Introduce nUm de carta: ");
        //scanf("%d", &c);
        for(i = 0 ; i < c ; i++)
        {
            r = pop(P1R2);
            push(temp, r);
        }

        nT = pop(temp);

        while(peek(temp) != NULL)
        {
            r = pop(temp);
            push(P1R2, r);
        }
        //printf("\n\n");
    }

    //printf("[P1] Type: %c level: %d\n", nT->type, nT->level);
    //printf("[P2] Type: %c level: %d\n", nT2->type, nT2->level);

    //CONDICIONES GOBLIN Y KNIGHT
    if (D->t == 1 && nT->type == 'K' && nT2->type == 'G')
    {
        push(V1, nT);
        push(V1, nT2);
        D->t = 0;
    }
    else if(D->t == 0 && nT2->type == 'K' && nT->type == 'G')
    {
        push(V2, nT);
        push(V2, nT2);
        D->t = 1;
    }
        //COMPARACIONES DE MISMA CLASE
    else if(nT->type == nT2->type)
    {
        if(nT->type == 'E' && nT->type == 'E') //caso 2 enanos
        {
            if(nT->level < nT2->level)
            {
                push(V1, nT);
                push(V1, nT2);
                D->t = 1;
            }
            else if(nT2->level < nT->level)
            {
                push(V2, nT);
                push(V2, nT2);
                D->t = 0;
            }
        }
        else if(nT->level > nT2->level)
        {
            push(V1, nT);
            push(V1, nT2);
            D->t = 0;
        }
        else if(nT->level < nT2->level)
        {
            push(V2, nT);
            push(V2, nT2);
            D->t=1;
        }
    }
        //COMPARACIONES DE DIFERENTE CLASE SIN DUPPLEGANGER
    else if(nT->type != nT2->type && nT->type != 'D' &&  nT2->type != 'D')
    {
        if(nT->type == 'E' || nT2->type == 'E') //enano perdedor
        {
            push(V1, nT);
            push(V2, nT2);
        }
        else if(D->t == 0)
        {
            push(V1, nT);
            push(V1, nT2);
            //D->t = 0; al estar implicito
        }
        else if(D->t == 1)
        {
            push(V2, nT);
            push(V2, nT2);
            //D->t = 1; al estar implicito
        }
    }
        //COMPARACIONES DE DIFERENTE CLASE CON DUPPLEGANGER
        //////
    else if(D->t == 0 && nT->type == 'D')
    {
        if(nT2->type != 'D' )
        {
            if(nT2->type == 'E') //enano perdedor
            {
                push(V1, nT);
                push(V2, nT2);
            }
            else
            {
                push(V1, nT);
                push(V1, nT2);
                D->t = 0;
            }
        }
        else if(nT2->type == 'D')
        {
            if(nT->level > nT2->level )
            {
                push(V1, nT);
                push(V1, nT2);
                D->t = 0;
            }
            else if(nT->level < nT2->level )
            {
                push(V2, nT);
                push(V2, nT2);
                D->t = 1;
            }
        }
    }
    else if(D->t == 1 && nT2->type == 'D')
    {
        if(nT->type != 'D' )
        {
            if(nT2->type == 'E') //enano perdedor
            {
                push(V1, nT);
                push(V2, nT2);
            }
            else
            {
                push(V2, nT);
                push(V2, nT2);
                D->t = 1;
            }
        }
        else if(nT->type == 'D')
        {
            if(nT->level > nT2->level )
            {
                push(V1, nT);
                push(V1, nT2);
                D->t = 0;
            }
            else if(nT->level < nT2->level)
            {
                push(V2, nT);
                push(V2, nT2);
                D->t = 1;
            }
        }
    }
    else if(nT->type == 'D' || nT2->type == 'D')
    {
        if(nT->level > nT2->level)
        {
            if(nT2->type == 'E') //enano perdedor
            {
                push(V1, nT);
                push(V2, nT2);
            }
            else
            {
                push(V1, nT);
                push(V1, nT2);
                D->t = 0;
            }
        }
        else if(nT->level < nT2->level)
        {
            if(nT->type == 'E') //enano perdedor
            {
                push(V1, nT);
                push(V2, nT2);
            }
            else
            {
                push(V2, nT);
                push(V2, nT2);
                D->t = 1;
            }
        }
    }
}
/*
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
*/
void claimWinner(Stack *V1, Stack *V2)
{
    int P1TG = 0;
    int P1TE = 0;
    int P1TN = 0;
    int P1TD = 0;
    int P1TK = 0;
    int VT1 = 0;
    int P1GMax = 0;
    int P1EMax = 0;
    int P1NMax = 0;
    int P1DMax = 0;
    int P1KMax = 0;

    while(peek(V1) != NULL)
    {
        if(V1->head->type == 'G')
        {
            if(V1->head->level > P1GMax)
                P1GMax = V1->head->level;

            P1TG++;
        }
        else if(V1->head->type == 'E')
        {
            if(V1->head->level > P1EMax)
                P1EMax = V1->head->level;

            P1TE++;
        }
        else if(V1->head->type == 'N')
        {
            if(V1->head->level > P1NMax)
                P1NMax = V1->head->level;

            P1TN++;
        }
        else if(V1->head->type == 'D')
        {
            if(V1->head->level > P1DMax)
                P1DMax = V1->head->level;

            P1TD++;
        }
        else if(V1->head->type == 'K')
        {
            if(V1->head->level > P1KMax)
                P1KMax = V1->head->level;

            P1TK++;
        }

        pop(V1);
    }

    int P2TG = 0;
    int P2TE = 0;
    int P2TN = 0;
    int P2TD = 0;
    int P2TK = 0;
    int VT2 = 0;
    int P2GMax = 0;
    int P2EMax = 0;
    int P2NMax = 0;
    int P2DMax = 0;
    int P2KMax = 0;

    while(peek(V2) != NULL)
    {
        if(V2->head->type == 'G')
        {
            if(V2->head->level > P2GMax)
                P2GMax = V2->head->level;

            P2TG++;
        }
        else if(V2->head->type == 'E')
        {
            if(V2->head->level > P2EMax)
                P2EMax = V2->head->level;

            P2TE++;
        }
        else if(V2->head->type == 'N')
        {
            if(V2->head->level > P2NMax)
                P2NMax = V2->head->level;

            P2TN++;
        }
        else if(V2->head->type == 'D')
        {
            if(V2->head->level > P2DMax)
                P2DMax = V2->head->level;

            P2TD++;
        }
        else if(V2->head->type == 'K')
        {
            if(V2->head->level > P2KMax)
                P2KMax = V2->head->level;

            P2TK++;
        }

        pop(V2);
    }
    /*
    printf("\n[P1TG]: %d\t[P1TE]: %d\t[P1TN]: %d\t[P1TD]: %d\t[P1TK]: %d\t\n", P1TG, P1TE, P1TN, P1TD, P1TK);
    printf("[P1GMax]: %d\t[P1EMax]: %d\t[P1NMax]: %d\t[P1DMax]: %d\t[P1KMax]: %d\t\n", P1GMax, P1EMax, P1NMax, P1DMax, P1KMax);

    printf("\n[P2TG]: %d\t[P2TE]: %d\t[P2TN]: %d\t[P2TD]: %d\t[P2TK]: %d\t\n", P2TG, P2TE, P2TN, P2TD, P2TK);
    printf("[P2GMax]: %d\t[P2EMax]: %d\t[P2NMax]: %d\t[P2DMax]: %d\t[P2KMax]: %d\t\n", P2GMax, P2EMax, P2NMax, P2DMax, P2KMax);
    */
    //Goblins
    if(P1TG > P2TG)
    {
        //printf("Mas Goblins Votaron por el Jugador 1\n");
        VT1++;
    }
    else if(P2TG > P1TG)
    {
        //printf("Mas Goblins Votaron por el Jugador 2\n");
        VT2++;
    }
    else if(P1TG == P2TG)
    {
        //printf("Empate\n");

        if(P1GMax > P2GMax)
        {
            //printf("El Jugador 1 Tiene el voto del Goblin mas alto, por lo que se lleva el voto de los Goblins\n");
            VT1++;
        }
        else if(P2GMax > P1GMax)
        {
            //printf("El Jugador 2 Tiene el voto del Goblin mas alto, por lo que se lleva el voto de los Goblins\n");
            VT2++;
        }
    }

    //Enanos
    if(P1TE > P2TE)
    {
        //printf("Mas Enanos Votaron por el Jugador 1\n");
        VT1++;
    }
    else if(P2TE > P1TE)
    {
        //printf("Mas Enanos Votaron por el Jugador 2\n");
        VT2++;
    }
    else if(P1TE == P2TE)
    {
        //printf("Empate\n");

        if(P1EMax > P2EMax)
        {
            //printf("El Jugador 1 Tiene el voto del Enano mas alto, por lo que se lleva el voto de los Enanos\n");
            VT1++;
        }
        else if(P2EMax > P1EMax)
        {
            //printf("El Jugador 2 Tiene el voto del Enano mas alto, por lo que se lleva el voto de los Enanos\n");
            VT2++;
        }
    }

    //necromancers
    if(P1TN > P2TN)
    {
        //printf("Mas Necromancers Votaron por el Jugador 1\n");
        VT1++;
    }
    else if(P2TN > P1TN)
    {
        //printf("Mas Necromancers Votaron por el Jugador 2\n");
        VT2++;
    }
    else if(P1TN == P2TN)
    {
        //printf("Empate\n");

        if(P1NMax > P2NMax)
        {
            //printf("El Jugador 1 Tiene el voto del Necromancer mas alto, por lo que se lleva el voto de los Necromancers\n");
            VT1++;
        }
        else if(P2NMax > P1NMax)
        {
            //printf("El Jugador 2 Tiene el voto del Necromancer mas alto, por lo que se lleva el voto de los Necromancers\n");
            VT2++;
        }
    }

    //doppelgangers
    if(P1TD > P2TD)
    {
        //printf("Mas Doppelgangers Votaron por el Jugador 1\n");
        VT1++;
    }
    else if(P2TD > P1TD)
    {
        //printf("Mas Doppelgangers Votaron por el Jugador 2\n");
        VT2++;
    }
    else if(P1TD == P2TD)
    {
        //printf("Empate\n");

        if(P1DMax > P2DMax)
        {
            //printf("El Jugador 1 Tiene el voto del Doppelganger mas alto, por lo que se lleva el voto de los Doppelgangers\n");
            VT1++;
        }
        else if(P2DMax > P1DMax)
        {
            //printf("El Jugador 2 Tiene el voto del Doppelganger mas alto, por lo que se lleva el voto de los Doppelgangers\n");
            VT2++;
        }
    }

    //knights
    if(P1TK > P2TK)
    {
        //printf("Mas Knights Votaron por el Jugador 1\n");
        VT1++;
    }
    else if(P2TK > P1TK)
    {
        //printf("Mas Knights Votaron por el Jugador 2\n");
        VT2++;
    }
    else if(P1TK == P2TK)
    {
        //printf("Empate\n");

        if(P1KMax > P2KMax)
        {
            //printf("El Jugador 1 Tiene el voto del Knight mas alto, por lo que se lleva el voto de los Knights\n");
            VT1++;
        }
        else if(P2KMax > P1KMax)
        {
            //printf("El Jugador 2 Tiene el voto del Knight mas alto, por lo que se lleva el voto de los Knights\n");
            VT2++;
        }
    }

    //decision de GANADOR FINAL

    if(VT1 > VT2)
        printf("!Gana el Jugador 1!\n");
    else if(VT2 > VT1)
        printf("!Gana el Jugador 2!\n");
}