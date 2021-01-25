#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    // ensure proper usage
    if (argc != 2)
    {
        fprintf(stderr, "Usage: recover image\n");
        return 1;
    }

    //pointer for image file to be recovered
    char *infile = argv[1];
    
    //open image file
    FILE *inptr = fopen(infile, "r");
    if (inptr == NULL)
    {
        fprintf(stderr, "Could not open %s.\n", infile);
        return 2;
    }

    //open file for recover jpegs
    FILE *img = NULL;

    //create buffer for each chunk of memory to be read into
    unsigned char buffer [512];

    //create variable to count number of jpeg files
    int counter = 0;
    
    //variable to hold filename
    char filename[8];
    
    //while loop condition to read 512 Bytes of data to file
    while (fread(&buffer, sizeof(char), 512, inptr) == 512)
    {

        //check first four bytes to see if we have the start of a new jpeg file
        if (buffer [0] == 0xff && buffer [1] == 0xd8 && buffer [2] == 0xff && (buffer [3] & 0xf0) == 0xe0)
        {

            //create jpeg filename
            sprintf(filename, "%03i.jpg", counter);
            
            //open image file
            img = fopen(filename, "w");
            if (img == NULL)
            {
                fprintf(stderr, "Could not create %s.\n", filename);
                return 3;
            }

            //write chunk of data to file
            fwrite(&buffer, sizeof(char), 512, img);
            
            //increase counter value
            counter ++;
        }

        //if we are on the same file continue to write the data block
        else
        {
            img = fopen(filename, "a");
            if (img == NULL)
            {
                fprintf(stderr, "Could not create %s.\n", filename);
                return 3;
            }
            fwrite(&buffer, sizeof(char), 512, img);
        }
        
        fclose(img);
        
    }   
    



    fclose(inptr);

    return 0;
}
