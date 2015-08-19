/*
    Greedy
    
    Author: Allen Whearry
    
    This is a solution of the greedy algorithm from
    pset1 of CS50x Harvard.
*/

#include <cs50.h>
#include <math.h>
#include <stdio.h>

int main(void)
{
    int q = 25;
    int d = 10;
    int n = 5;
    int p = 1;
    int cc = 0;
    float c;
    
    do {
    printf("How much change: ");
    c = (int)round(GetFloat() * 100);
    }
    while (c < 0);
    
    while (c >= q)
    {
        cc++;
        c = c - q;
    }
    while (c < q && c >= d)
    {
        cc++;
        c = c - d;
    }
    while (c < d && c >= n)
    {
        cc++;
        c = c - n;
    }
    while (c >= p && c < n)
    {
        cc++;
        c = c - p;
    }
    
    printf("%i\n",cc);
    return 0;
}
