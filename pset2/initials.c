/***********************************************************
** Allen Whearry Jr.
*
** instagram.com/NoRest4AWhearry
*
** Initials:
*
** This is a solution of the "Initials" problem from
** pset2 of CS50x Harvard. Initials takes user's full name
** and outputs the their initials capitalized.
************************************************************/
#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

int main(void)
{
    // Get string from user
    string name = GetString();
    
    // Print first index of name
    printf("%c", toupper(name[0]));
    
    // iterate over all letters of name
    for (int i = 0; i < strlen(name); i++)
    {
        // if space found, print next char
        if (name[i] == ' ')
        {
            printf("%c", toupper(name[i + 1]));  
        }
    }
    printf("\n");
    return 0;
}
