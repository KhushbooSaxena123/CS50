#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <cs50.h>

typedef uint8_t BYTE;
int main(int argc, char *argv[])
{
    char filename[20];
    FILE *img = NULL;
    int count = 0, found = 0; //count will keep treck of file number.
    if (argc != 2)        // ensuring a only two command line argument.
    {
        printf("Usage: ./recover name of forensic image");
        return 1;
    }
    FILE *file = fopen(argv[1], "r");   // opening input card file.
    if (! file)
    {
        printf("could not open %s \n", argv[1]);
        return 1;
    }
    BYTE buffer[512];
    while (fread(&buffer, sizeof(BYTE), 512, file))  //reading file 512 bytes from input file.
    {
        // checking if their header are for the Header of jpg.
        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] & 0xf0) == 0xe0)
        {
            if (found == 1)
            {
                fclose(img);
            }
            sprintf(filename, "%03i.jpg", count);  // naming files number wise.
            img = fopen(filename, "w");  // writing in output file.
            fwrite(&buffer, sizeof(BYTE), 512, img);
            count++;
            found = 1;  // if found thus enable found
        }
        else if (found == 1)  //if not found writing in same file that found.
        {
            fwrite(&buffer, sizeof(BYTE), 512, img);
        }

    }
    //closing files
    fclose(img);
    fclose(file);

}