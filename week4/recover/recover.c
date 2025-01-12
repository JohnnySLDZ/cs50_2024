#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

typedef uint8_t byte;
int blockSize = 512;

int main(int argc, char *argv[])
{
    //open file
    if (argc != 2)
    {
        printf("File was not found\n");
        printf("Usage: ./recover FILE\n");
        return 1;
    }

    FILE *raw = fopen(argv[1], "rb");

    if(raw != NULL)
    {
        printf("%p\n",raw);
    }
    else
    {
        printf("failed\n");
        return 2;
    }
    //create a buffer
    byte *buffer = malloc(sizeof(byte)*512);
    //while there if bytes to read
    //read 512 bytes of the file
    char fileName[8];
    int files = 0;
    int writing = 0;
    FILE *jpg;

    while(fread(buffer, sizeof(byte), blockSize, raw) == blockSize)
    {
    //     //seach for the jpg signature at the begining of the block
    //     //if jpg signature if found open a file
        if((*(buffer+0) == 0xff && *(buffer+1)==0xd8 && *(buffer+2)==0xff && (*(buffer+3) & 0xf0) == 0xe0))
        {
            if(writing == 1)
            {
                fclose(jpg);
                files++;
            }
            sprintf(fileName, "%03i.jpg", files);
            jpg = fopen(fileName, "w");
            if(jpg != NULL)
            {
                fwrite(buffer, sizeof(byte), blockSize, jpg);
                writing = 1;
            }
            else
            {
                printf("failed\n");
                return 2;
            }
        }
        else if(writing == 1)
        {
            fwrite(buffer, sizeof(byte), blockSize, jpg);
        }
    }
    fclose(jpg);
    free(buffer);
    fclose(raw);
}
