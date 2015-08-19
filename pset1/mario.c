/***********************************************************
** Allen Whearry Jr.
*
** instagram.com/NoRest4AWhearry
*
** Mario:
*
** This is a solution of "Mario" from
** pset1 of CS50x Harvard.
************************************************************/
#include <stdio.h>
#include <cs50.h>

int main(void)
{
    int height;
    do
    {
        printf("Height:");
        height = GetInt();
        if (height == 0)
        {
            return 0;
        }
    }
    while(height < 1 || height >= 24); 
    
    // Create correct number of rows
    for(int row = 0; row < height; row++) 
    {
    // Create corret number of spaces
        for(int space = 0; space < height - row - 1; space++)
        {
            printf("%s", " ");
        }
        // Create correct number of hashes.       
        for(int hash = 0; hash < row + 2; hash++)
        {
            printf("%s", "#");
		}
		
        printf("\n");
	}	
    return 0;
}
