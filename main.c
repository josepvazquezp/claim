#include <stdio.h>
#include <stdlib.h>
#include "raylib.h"
#include <time.h>
#include "claim.h"
#include "stack.h"

int main(void) {
    const int screenWidth = 1600;
    const int screenHeight = 900;
    int start = 1;

    InitWindow(screenWidth, screenHeight, "CLAIM");

    SetTargetFPS(60);

    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        BeginDrawing();

        if(start == 1)
            drawStart();

        if(GetKeyPressed() == KEY_ENTER)
            start = 0;

        if(start == 0)
            drawTable();

        Stack *V1 = newStack();
        Stack *V2 = newStack();
        Stack *D = newDeck();

        Stack *P1 = newPlayer(D);

        Stack *P2 = newPlayer(D);

        Stack *P1R2 = newStack();
        Stack *P2R2 = newStack();

        /*
        while (peek(D) != NULL)
        {
            itsGoTimeBBY(D, V1, V2, P1, P2, P1R2, P2R2);
        }

        while (peek(P1R2) != NULL && peek(P2R2) != NULL)
        {
            round2(D, V1, V2, P1R2, P2R2);
        }
         */

        //claimWinner(V1, V2);

        EndDrawing();
    }

    CloseWindow();

    return 0;
}