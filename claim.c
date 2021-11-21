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

void itsGoTimeBBY(Stack *D, Stack *V1, Stack *V2, Stack *P1, Stack *P2, Stack *P1R2, Stack *P2R2)
{
   
    Stack *temp = newStack();
    Node *tC = pop(D);
    Node *nT;
    Node *nT2;
    Node *r;
    int c;
    int i;

    printf("[Deck] Type: %c level: %d\n\n", tC->type, tC->level);

    if(D->t == 0)
    {
        displayD(P1);
        printf("[P1] Introduce nUm de carta: ");
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
        printf("\n\n");
        
        displayD(P2);
        printf("[P2] Introduce nUm de carta: ");
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
        printf("\n\n");
    }
    else if(D->t == 1)
    {
        displayD(P2);
        printf("[P2] Introduce nUm de carta: ");
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
        printf("\n\n");

        displayD(P1);
        printf("[P1] Introduce nUm de carta: ");
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
        printf("\n\n");
    }

    printf("[Deck] Type: %c level: %d\n", tC->type, tC->level);
    printf("[P1] Type: %c level: %d\n", nT->type, nT->level);
    printf("[P2] Type: %c level: %d\n", nT2->type, nT2->level);

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
            push(V2, nT2);
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

    displayD(P1R2);
    displayD(V1);
    printf("--------\n\n");
    displayD(P2R2);
    displayD(V2);
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
        displayD(P1R2);
        printf("[P1] Introduce nUm de carta: ");
        scanf("%d", &c);
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
        printf("\n\n");

        displayD(P2R2);
        printf("[P2] Introduce nUm de carta: ");
        scanf("%d", &c);
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
        printf("\n\n");
    }
    else if (D->t == 1)
    {
        displayD(P2R2);
        printf("[P2] Introduce nUm de carta: ");
        scanf("%d", &c);
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
        printf("\n\n");

        displayD(P1R2);
        printf("[P1] Introduce nUm de carta: ");
        scanf("%d", &c);
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
        printf("\n\n");
    }

    printf("[P1] Type: %c level: %d\n", nT->type, nT->level);
    printf("[P2] Type: %c level: %d\n", nT2->type, nT2->level);
    
    //CONDICIONES GOBLIN Y KNIGHT
    if (D->t == 1 && nT->type == 'K' && nT2->type == 'G')
    {
        push(V1,nT);
        push(V1,nT2);
        D->t = 0;
    }
    else if(D->t == 0 && nT2->type == 'K' && nT->type == 'G')
    {
        push(V2,nT);
        push(V2,nT2);
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
            push(V1,nT);
            push(V1,nT2);
            D->t = 0;
        }
        else if(nT->level < nT2->level)
        {
            push(V2,nT);
            push(V2,nT2);
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
            push(V1,nT);
            push(V1,nT2);
            //D->t = 0; al estar implicito
        }
        else if(D->t == 1)
        {
            push(V2,nT);
            push(V2,nT2);
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
                push(V1,nT);
                push(V2,nT2);
            }
            else
            {
                push(V1,nT);
                push(V1,nT2);
                D->t = 0;
            }
        }
        else if(nT2->type == 'D')
        {
            if(nT->level > nT2->level )
            { 
                push(V1,nT);
                push(V1,nT2);
                D->t = 0;
            }
            else if(nT->level < nT2->level )
            { 
                push(V2,nT);
                push(V2,nT2);
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
                push(V1,nT);
                push(V2,nT2);
            }
            else
            {
                push(V2,nT);
                push(V2,nT2);
                D->t = 1;
            }
        }
        else if(nT->type == 'D')
        {
            if(nT->level > nT2->level )
            { 
                push(V1,nT);
                push(V1,nT2);
                D->t = 0;
            }
            else if(nT->level < nT2->level)
            { 
                push(V2,nT);
                push(V2,nT2);
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
                push(V1,nT);
                push(V2,nT2);   
            } 
            else
            {
                push(V1,nT);
                push(V1,nT2);
                D->t = 0;
            }
        }
        else if(nT->level < nT2->level)
        { 
            if(nT->type == 'E') //enano perdedor
            {
                push(V1,nT);
                push(V2,nT2);   
            }
            else
            { 
                push(V2,nT);
                push(V2,nT2);
                D->t = 1;
            }
        }
    }
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
void ClaimWinner(Stack *V1, Stack *V2){
    //SUMA DE VOTANTES DE PLAYER 1
    Stack *TempP1 = newStack();
    int P1TG = 0;
    int P1TE = 0;
    int P1TN = 0;
    int P1TD = 0;
    int P1TK = 0;
    int VT1 = 0;   
    int P1MAX=0; 
    while(peek(V1)!=NULL){
      if (V1->head->type == 'G')
        P1TG++;
      else if (V1->head->type == 'E')
        P1TE++;
      else if (V1->head->type == 'N')
        P1TN++;
      else if (V1->head->type == 'D')
        P1TD++;
      else if (V1->head->type == 'K')
        P1TK++;
      push(TempP1,pop(V1));
    }
    //SUMA DE VOTANTES DE PLAYER 2
     Stack *TempP2 = newStack();
    int P2TG = 0;
    int P2TE = 0;
    int P2TN = 0;
    int P2TD = 0;
    int P2TK = 0;
    int VT2 = 0;   
    int P2MAX=0;

    while(peek(V2)!=NULL){
      if (V2->head->type == 'G')
        P2TG++;
      else if (V2->head->type == 'E')
        P2TE++;
      else if (V2->head->type == 'N')
        P2TN++;
      else if (V2->head->type == 'D')
        P2TD++;
      else if (V2->head->type == 'K')
        P2TK++;
      push(TempP2,pop(V2));
    }
    int c = 0;
    //COMPARACIONES 

    //COMP G
    if (P1TG > P2TG){
      printf("Mas Goblins Votaron por el Jugador 1\n");
      VT1++;
    }

    else if  (P2TG > P1TG){
      printf("Mas Goblins Votaron por el Jugador 2\n");
      VT2++;
    }

    else{

      printf("Empate\n");

      

      while(peek(TempP2)!=NULL){

      if (c == 0 &&TempP2->head->type == 'G'){
        P2MAX=TempP2->head->level;
        c++;
        }

      if (TempP2->head->type == 'G'){
          if (TempP2->head->level > P2MAX){
            P2MAX=TempP2->head->level;
          }
      }
  
      push(V2,pop(TempP2));
      }

    c = 0;

      while(peek(TempP1)!=NULL){

      if (c == 0 && TempP1->head->type == 'G'){
        P1MAX=TempP1->head->level;
        c++;
        }

      if (TempP1->head->type == 'G'){
          if (TempP1->head->level > P1MAX){
            P1MAX=TempP1->head->level;
          }
      }
  
      push(V1,pop(TempP1));
      }

      c = 0;

      if (P2MAX > P1MAX){ 
        printf("El Jugador 2 Tiene el voto del Goblin mas alto, por lo que se lleva el voto de los Goblins"); 
        VT2++;
      } 
      else if (P2MAX < P1MAX){ 
        printf("El Jugador 1 Tiene el voto del Goblin mas alto, por lo que se lleva el voto de los Goblins"); 
        VT1++;
      } 

      while(peek(V1)!=NULL){
         push(TempP1,pop(V1));
      }
      while(peek(V2)!=NULL){
         push(TempP2,pop(V2));
      }

    }



    //COMP ENANOS
    if (P1TE > P2TE){
      printf("Mas Enanos Votaron por el Jugador 1\n");
      VT1++;
    }

    else if  (P2TE > P1TE){
      printf("Mas Enanaos Votaron por el Jugador 2\n");
      VT2++;
    }

    else{

      printf("Empate\n");

     
      c = 0;
      while(peek(TempP2)!=NULL){

        if (c == 0 &&TempP2->head->type == 'E' ){
        P2MAX=TempP2->head->level;
        c++;
        }

      if (TempP2->head->type == 'E'){
          if (TempP2->head->level > P2MAX){
            P2MAX=TempP2->head->level;
          }
      }
  
      push(V2,pop(TempP2));
      }
       c = 0;
      while(peek(TempP1)!=NULL){

       if (c == 0 &&TempP1->head->type == 'E'){
        P1MAX=TempP1->head->level;
        c++;
        }

      if (TempP1->head->type == 'E'){
          if (TempP1->head->level > P1MAX){
            P1MAX=TempP1->head->level;
          }
      }
  
      push(V1,pop(TempP1));
      
      }
      c = 0;

      if (P2MAX > P1MAX){ 
        printf("El Jugador 2 Tiene el voto del Enano mas alto, por lo que se lleva el voto de los Enanos"); 
        VT2++;
      } 
      else if (P2MAX < P1MAX){ 
        printf("El Jugador 1 Tiene el voto del Enano mas alto, por lo que se lleva el voto de los Enanos"); 
        VT1++;
      } 

      while(peek(V1)!=NULL){
         push(TempP1,pop(V1));
      }
      while(peek(V2)!=NULL){
         push(TempP2,pop(V2));
      }

    }

    //COMP NECROMANCERS
    if (P1TN > P2TN){
      printf("Mas Necromancers Votaron por el Jugador 1\n");
      VT1++;
    }

    else if  (P2TN > P1TN){
      printf("Mas Necromancers Votaron por el Jugador 2\n");
      VT2++;
    }

    else{

      printf("Empate\n");

     
      c = 0;
      while(peek(TempP2)!=NULL){

        if (c == 0 &&TempP2->head->type == 'N' ){
        P2MAX=TempP2->head->level;
        c++;
        }

      if (TempP2->head->type == 'N'){
          if (TempP2->head->level > P2MAX){
            P2MAX=TempP2->head->level;
          }
      }
  
      push(V2,pop(TempP2));
      }
       c = 0;

      while(peek(TempP1)!=NULL){

       if (c == 0 &&TempP1->head->type == 'N'){
        P1MAX=TempP1->head->level;
        c++;
        }

      if (TempP1->head->type == 'N'){
          if (TempP1->head->level > P1MAX){
            P1MAX=TempP1->head->level;
          }
      }
  
      push(V1,pop(TempP1));
      
      }

      c = 0;

      if (P2MAX > P1MAX){ 
        printf("El Jugador 2 Tiene el voto del necromancer mas alto, por lo que se lleva el voto de los necromancers"); 
        VT2++;
      } 
      else if (P2MAX < P1MAX){ 
        printf("El Jugador 1 Tiene el voto del necromancer mas alto, por lo que se lleva el voto de los necromancers"); 
        VT1++;
      } 

      while(peek(V1)!=NULL){
         push(TempP1,pop(V1));
      }
      while(peek(V2)!=NULL){
         push(TempP2,pop(V2));
      }

    }

    //COMP DOPPELGANGERS
    if (P1TN > P2TN){
      printf("Mas Doppelgangers Votaron por el Jugador 1\n");
      VT1++;
    }

    else if  (P2TN > P1TN){
      printf("Mas Doppelgangers Votaron por el Jugador 2\n");
      VT2++;
    }

    else{

      printf("Empate\n");

     
      c = 0;
      while(peek(TempP2)!=NULL){

        if (c == 0 &&TempP2->head->type == 'D' ){
        P2MAX=TempP2->head->level;
        c++;
        }

      if (TempP2->head->type == 'D'){
          if (TempP2->head->level > P2MAX){
            P2MAX=TempP2->head->level;
          }
      }
  
      push(V2,pop(TempP2));
      }
       c = 0;

      while(peek(TempP1)!=NULL){

       if (c == 0 &&TempP1->head->type == 'D'){
        P1MAX=TempP1->head->level;
        c++;
        }

      if (TempP1->head->type == 'D'){
          if (TempP1->head->level > P1MAX){
            P1MAX=TempP1->head->level;
          }
      }
  
      push(V1,pop(TempP1));
      
      }

      c = 0;

      if (P2MAX > P1MAX){ 
        printf("El Jugador 2 Tiene el voto del Doppelganger mas alto, por lo que se lleva el voto de los Doppelgangers"); 
        VT2++;
      } 
      else if (P2MAX < P1MAX){ 
        printf("El Jugador 1 Tiene el voto del Doppelganger mas alto, por lo que se lleva el voto de los Doppelgangers"); 
        VT1++;
      } 

      while(peek(V1)!=NULL){
         push(TempP1,pop(V1));
      }
      while(peek(V2)!=NULL){
         push(TempP2,pop(V2));
      }

    }

    //COMP KNIGHTS
    if (P1TN > P2TN){
      printf("Mas Caballeros Votaron por el Jugador 1\n");
      VT1++;
    }

    else if  (P2TN > P1TN){
      printf("Mas Caballeros Votaron por el Jugador 2\n");
      VT2++;
    }

    else{

      printf("Empate\n");

     
      c = 0;
      while(peek(TempP2)!=NULL){

        if (c == 0 &&TempP2->head->type == 'K' ){
        P2MAX=TempP2->head->level;
        c++;
        }

      if (TempP2->head->type == 'K'){
          if (TempP2->head->level > P2MAX){
            P2MAX=TempP2->head->level;
          }
      }
  
      push(V2,pop(TempP2));
      }
       c = 0;

      while(peek(TempP1)!=NULL){

       if (c == 0 &&TempP1->head->type == 'K'){
        P1MAX=TempP1->head->level;
        c++;
        }

      if (TempP1->head->type == 'K'){
          if (TempP1->head->level > P1MAX){
            P1MAX=TempP1->head->level;
          }
      }
  
      push(V1,pop(TempP1));
      
      }

      c = 0;

      if (P2MAX > P1MAX){ 
        printf("El Jugador 2 Tiene el voto del Caballero, por lo que se lleva el voto de los Caballeros"); 
        VT2++;
      } 
      else if (P2MAX < P1MAX){ 
        printf("El Jugador 1 Tiene el voto del Caballero mas alto, por lo que se lleva el voto de los Caballeros"); 
        VT1++;
      } 

      while(peek(V1)!=NULL){
         push(TempP1,pop(V1));
      }
      while(peek(V2)!=NULL){
         push(TempP2,pop(V2));
      }

    }

    //DECISION DE GANADOR FINAL

    if (VT1 > VT2)
      printf("¡Gana el Jugador 1!\n");

    else if (VT2 > VT1)
      printf("¡Gana el Jugador 2!");
}
