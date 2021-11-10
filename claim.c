#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "claim.h"
#include "stack.h"

deck *newGame()
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

    deck *D = malloc(sizeof(deck));
    int e;

    for(i = 0 ; i < 52 ; i++)
    {
        e = (int*)temp[i][0];
        D->top->level = e - 48;
        D->top->type = temp[i][1];

        //printf("Type: %c with level: %d\n", D->top->type, D->top->level);
    }

    return D;    

}
