/**
 * helpers.c
 *
 * Computer Science 50
 * Problem Set 3
 *
 * Helper functions for Problem Set 3.
 */
       
#include <cs50.h>

#include "helpers.h"

/**
 * Returns true if value is in array of n values, else false.
 */
bool search(int value, int values[], int n)
{
    int min = 0;
    int max = n;
    int midpoint;
    if ( value < 0 )
    {
        return false;
    }
    
    if (max < min)
    {
        return false;
    } 
    
    while(min <= max)
    {
        sort(values, n);
        midpoint = (min + max) / 2;
         
        if (values[midpoint] == value)
        {
            return true;
        }
        else if (values[midpoint] > value)
        {
            max = midpoint - 1;
        }
        else if (values[midpoint] < value)
        {
            min = midpoint + 1;
        }
    }
    return false;
}

/**
 * Sorts array of n values.
 */
void sort(int values[], int n)
{
    int i, j, temp;
     
    for (i = 0; i < n -1; i++)
    {
        for (j = i + 1; j < n; j++)
        {
            if (values[i] > values [j])
            {
                temp = values[i];
                values[i] = values[j];
                values[j] = temp;
            }
        }
    }
    return;
}
