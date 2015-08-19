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

int main(int argc, string argv[])
{
    // check if main has only 2 arguments
    if (argc != 2)
    {
        printf("FAIL\n");
        return 1;
    }
    
    // chage argv[1] to an integer
    int  k = atoi(argv[1]);
    
    // if K > 26
    if (k > 26)
    {
        k = k % 26;
    }
    
    // get string from user
    string p = GetString();
    
    // iterate over string
    for (int i = 0; i < strlen(p); i++)
    {
        // Check if letter is lowercass or uppercase
        if ( isupper(p[i]) || islower(p[i]) )
        {
            char offset = p[i] + k;
            // new char is 
            if ( offset < 65 || (offset > 90 && offset < 97) || offset > 122)
            {
                printf("%c", offset - 26);
            }
            else
            {
                printf("%c", offset);
            }    
        }
        // if letter IS NOT between 'a' & 'z' or 'A' & 'Z'
        else
        {
            printf("%c", p[i]);
        }
    }
    printf("\n");
    return 0;
}
