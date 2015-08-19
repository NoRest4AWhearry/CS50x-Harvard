/***********************************************************
** Allen Whearry Jr.
*
** instagram.com/NoRest4AWhearry
*
** Greedy:
*
** This is a solution of the greedy algorithm from
** pset1 of CS50x Harvard.
************************************************************/
#include <cs50.h>
#include <math.h>
#include <stdio.h>

int main(void)
{
    int coins[] = {25, 10, 5, 1};
    int coin_count = 0;
    float change;
    
    do 
    {
        printf("How much change: ");
        change = (int) round(GetFloat() * 100);
    }
    while (change < 0);
    
    for (int i = 0; i < 4; i++)
    {
        while ( change >= coins[i])
        {
            coin_count++;
            change = change - coins[i];
        }
    }
    printf("%i\n",coin_count);
    return 0;
}
