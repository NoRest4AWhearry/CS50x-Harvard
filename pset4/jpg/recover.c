/***********************************************************
** Allen Whearry Jr.
*
** instagram.com/NoRest4AWhearry
*
** Recover:
*
** This is a solution of the "Recover" problem from
** pset4 of CS50x Harvard.
************************************************************/
#include <stdio.h>
#include <stdint.h>

int main(int argc, char* argv[])
{
    // TODO Open Memory Card
    FILE* memcard = fopen("card.raw", "r");
    
    if (memcard == NULL)
    {
        printf("Error opening file...");
        return 1;
    }
    
    FILE* img = NULL;
    
    // Jpg Counter
    int jpg_counter = 0;
    
    // Loop til end of file
    while(!feof(memcard))
    {
        uint8_t buffer[512];
        char title[8];
        
        // TODO Find beginning of jpg
        if (buffer[0] == 0xff 
            && buffer[1] == 0xd8 
            && buffer[2] == 0xff 
            && (buffer[3] == 0xe0 || buffer[3] == 0xe1))
        {
            if (img != NULL)
                fclose(img);
                
            // TODO Open a new jpg
            sprintf(title,"%03d.jpg", jpg_counter);
            img = fopen(title, "w");
            jpg_counter++;
            fwrite(buffer, sizeof(buffer), 1, img);
        
        }
        else
        {
            if (img != NULL)
                fwrite(buffer,sizeof(buffer),1, img);
        }
        fread(buffer, sizeof(buffer), 1, memcard);
    
    }
    if (img != NULL)
    {
        fclose(img);
    }
    
    fclose(memcard);
    return 0;
}

