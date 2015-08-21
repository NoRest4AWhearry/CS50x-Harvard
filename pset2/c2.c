/***********************************************************
** Allen Whearry Jr.
*
** instagram.com/NoRest4AWhearry
*
** Caesar Cipher:
*
** This is a solution of the "Caesar Cipher" problem from
** pset2 of CS50x Harvard.
************************************************************/
#include <cs50.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int main(void)
{
    int k = 'Z' % 65;
    int p = 'R' + k;
    int q = p - 26;
    printf("R + K[%i] = %i[%c] but should really be %i[%c]", k, p, p, q,q);
    return 0;
}
