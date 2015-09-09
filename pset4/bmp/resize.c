/***********************************************************
** Allen Whearry Jr.
*
** instagram.com/NoRest4AWhearry
*
** Resize:
*
** This is a solution of the "Resize" problem from
** pset4 of CS50x Harvard.
************************************************************/
       
#include <stdio.h>
#include <stdlib.h>

#include "bmp.h"

int main(int argc, char* argv[])
{
    // ensure proper usage
    if (argc != 4)
    {
        printf("Usage: ./resize n infile outfile\n");
        return 1;
    }

    // remember filenames
    int n = atoi(argv[1]);
    char* infile = argv[2];
    char* outfile = argv[3];
    if (n < 1 || n > 100)
    {
        printf("Usage: ./resize n infile outfile\n");
        printf("n must be an interger 1 - 100\n");
        return 2;
    }

    // open input file 
    FILE* inptr = fopen(infile, "r");
    if (inptr == NULL)
    {
        printf("Could not open %s.\n", infile);
        return 3;
    }

    // open output file
    FILE* outptr = fopen(outfile, "w");
    if (outptr == NULL)
    {
        fclose(inptr);
        fprintf(stderr, "Could not create %s.\n", outfile);
        return 4;
    }

    // read infile's BITMAPFILEHEADER
    BITMAPFILEHEADER bf, bf_resize;
    fread(&bf, sizeof(BITMAPFILEHEADER), 1, inptr);
    bf_resize = bf;

    // read infile's BITMAPINFOHEADER
    BITMAPINFOHEADER bi, bi_resize;
    fread(&bi, sizeof(BITMAPINFOHEADER), 1, inptr);
    bi_resize = bi;

    // ensure infile is (likely) a 24-bit uncompressed BMP 4.0
    if (bf.bfType != 0x4d42 || bf.bfOffBits != 54 || bi.biSize != 40 || 
        bi.biBitCount != 24 || bi.biCompression != 0)
    {
        fclose(outptr);
        fclose(inptr);
        fprintf(stderr, "Unsupported file format.\n");
        return 5;
    }

    // get the new dimensions
    bi_resize.biWidth  = bi.biWidth * n;
    bi_resize.biHeight = bi.biHeight * n;
    
    // get padding for scanlines
    int padding =  (4 - (bi.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;
    int padding_resize = (4 - (bi_resize.biWidth * sizeof(RGBTRIPLE)) %4) % 4;
    
    // get new image sizes
    bi_resize.biSizeImage = (bi_resize.biWidth * sizeof(RGBTRIPLE) + padding_resize) * abs(bi_resize.biHeight);
    bf_resize.bfSize = bf.bfSize - bi.biSizeImage + bi_resize.biSizeImage;
    
    // write outfile's BITMAPFILEHEADER
    fwrite(&bf_resize, sizeof(BITMAPFILEHEADER), 1, outptr);

    // write outfile's BITMAPINFOHEADER
    fwrite(&bi_resize, sizeof(BITMAPINFOHEADER), 1, outptr);

    // iterate over infile's scanlines
    for (int i = 0, biHeight = abs(bi.biHeight); i < biHeight; i++)
    {
        // iterate n times
        for (int j = 0; j < n; j++)
        {
            // iterate over pixels in scanline
            for (int k = 0; k < bi.biWidth; k++)
            {
                // temporary storage
                RGBTRIPLE triple;

                // read RGB triple from infile
                fread(&triple, sizeof(RGBTRIPLE), 1, inptr);

                // write RGB triple to outfile
                for (int l = 0; l < n; l++)
                {
                    fwrite(&triple, sizeof(RGBTRIPLE), 1, outptr);
                }
            }
            for(int p = 0; p < padding_resize; p++)
                fputc(0x00, outptr);
                
            if(j < n - 1)
                fseek(inptr, -bi.biWidth * sizeof(RGBTRIPLE), SEEK_CUR);
        }
        // skip over padding, if any
        fseek(inptr, padding, SEEK_CUR);
    }

    // close infile
    fclose(inptr);

    // close outfile
    fclose(outptr);

    // that's all folks
    return 0;
}
