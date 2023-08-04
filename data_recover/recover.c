#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

int main(int argc, char *argv[])
{
    // define BYTE as data type
    typedef uint8_t BYTE;
    // check usage
    if (argc != 2)
    {
        printf("usafe ./recover inputfile_name\n");
        return 1;
    }

    // open file memory and use a pointer to the begining of the file

    FILE *input = fopen(argv[1], "r");
    if (input == NULL)
    {
        printf("can not open file\n");
        return 2;
    }

    // read data

    BYTE buffer[512];           // buffer for the read data
    int counter = 0;            // counter for the recovered jpeg
    char *filename = malloc(8); // create a memory space for storage of file name; Name the output file xxx.jpg. so need 7+1 =8 byte of space. name a string as xxx.jpg
    FILE *image = NULL;         // create a pointer to the output file, initiated to NULL as an identifier. If NULL, then there have not yet found any jpg. Otherwise, there is already found jpg before.

    // create a loop for every 512 BYTE
    while (fread(&buffer, sizeof(BYTE), 512, input))
    {
        // printf("%p\n", &buffer);
        // printf("%p\n", &buffer[0]);
        // return 1;
        //  printf("first byte is %i\n", buffer[0]);
        //  printf("first byte is %i\n", buffer[1]);
        //  printf("first byte is %i\n", buffer[2]);
        //  printf("first byte is %i\n", buffer[3]);
        // printf("while works\n");
        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] & 0xf0) == 0xe0)
        {
            // now, the start of jpg is identified,
            // is this the first picture?
            if (image == NULL)
            {
                // this is the first pic
                sprintf(filename, "%03i.jpg", counter); // this name the file xxx.jpg and store the pointer file at the malloc(8)
                // printf("filenames are %s\n", filename);
                counter++;
                // image is a pointer vreated before and now we point it at a file (name defined above) as the output file.
                image = fopen(filename, "w");
                // write the 512 byte to the file pointed by the pointer image
                fwrite(&buffer[0], sizeof(BYTE), 512, image);
            }

            else
            {
                // in this case, we identify the start of a jpg file but it's not the first jpg file. So we have to close the last file and open a new file
                fclose(image);
                sprintf(filename, "%03i.jpg", counter);
                counter++;
                image = fopen(filename, "w");
                fwrite(&buffer[0], sizeof(BYTE), 512, image);
            }
        }

        else
        {
            // in this case, this frame is not the start of a jpg.it can either be a body of a jpg, or not a jpg (this case happened before the first jpg)
            if (image != NULL)
            {
                fwrite(&buffer[0], sizeof(BYTE), 512, image);
            }
        }
    }

    fclose(input);
    free(filename);

    // read the opened file to frame of 512 byte.

    // char *buffer[512];
    // sprintf(filename, "%03i.jpg",2);
}