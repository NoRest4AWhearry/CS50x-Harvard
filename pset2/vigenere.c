/***********************************************************
** Allen Whearry Jr.
*
** instagram.com/NoRest4AWhearry
*
** Vigenere Cipher:
*
** This is a solution of the "Vigenere Cipher" problem from
** pset2 of CS50x Harvard.
************************************************************/
#include <cs50.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
int key(char k);

int main(int argc, string argv[])
{
    // check if main has only 2 arguments
    if (argc != 2)
    {
        printf("FAIL\n");
        return 1;
    }
    
    // get string
    string k = (argv[1]);
    
    // make sure all chars in K are letters
    for (int j = 0; j < strlen(k); j++)
    {
        if ( !isalpha(k[j]) )
        {
            printf("FAIL\n");
            return 1;
        }
    }
    
    // get string from user
    string p = GetString();
    
    // iterate over string
    for (int i = 0, j = 0; i < strlen(p); i++)
    {
        // If char is a letter
        if ( isalpha(p[i]) )
        {
            // Do this to loop through string K
            j = j % strlen(k);
            
            char offset = p[i] + key(k[j]);
            
            //print coded letter
            if ( offset < 65 || (offset > 90 && offset < 97) || offset > 122 )
            {
                printf("%c", offset - 26);
            }
            else if ( isupper(p[i]) && offset > 90 )
            {
                printf("%c", offset - 26);
            }
            else
            {
                printf("%c", offset);
            }
            j++;
        }
        else
        {
            printf("%c",p[i]);
        }
    }
    printf("\n");
    return 0;
}

int key(char k)
{
    int key;
    if ( isupper(k) )
    {
        key = k % 65;
    }
    else
    {
        key = k % 97;
    }
    
    return key;
}
