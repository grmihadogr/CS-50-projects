#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#include "wav.h"

int check_format(WAVHEADER header);
int get_block_size(WAVHEADER header);

int main(int argc, char *argv[])
{
    // Ensure proper usage
    // TODO #1
    if (argc != 3)
    {
        printf("Usage: ./reverse input.wav output.wav\n");
        return 1;
    }
    // Open input file for reading
    // TODO #2

    // step1 create a pointer that point at the input/output file and initiate them with the argument value
    FILE *input = fopen(argv[1], "r");
    if (input == NULL)
    {
        printf("could not open input file\n");
        return 1;
    }

    // Read header
    // TODO #3

    // WAVHEADER wavheader = fread(&wavheader, sizeof(BYTE), 44, input);
    // This is wrong because the data structure is already include all the info of header. SO the
    WAVHEADER header;
    fread(&header, sizeof(WAVHEADER), 1, input);
    // Use check_format to ensure WAV format
    // TODO #4
    if (!check_format(header))
    {
        printf("unsupported format\n");
        return 2;
    }
    // Open output file for writing
    // TODO #5
    FILE *output = fopen(argv[2], "w");
    if (output == NULL)
    {
        printf("could not open output file\n");
    }
    // Write header to file
    // TODO #6
    fwrite(&header, sizeof(WAVHEADER), 1, output);

    // Use get_block_size to calculate size of block
    // TODO #7
    int blocksize = get_block_size(header);

    // Write reversed audio to file
    // TODO #8

    // create a buffer to story the each unit (aka blocksize) of reversed audio. The reversed buffer will be fread to buffer and fwrite to output file..
    BYTE buffer[blocksize];
    {
        // after fread the header, the pointer is at the beginging of audio date. find its location referred to the begining of the file.
        long starting = ftell(input);
        // move the pointer to the end of the file and find the relative location, then, find the block count.
        fseek(input, 0, SEEK_END);
        long ending = ftell(input);
        int blockcount = (ending - starting) / blocksize;
        // printf("starting is %li", starting );
        // printf("ending is %li", ending );

        // printf("blockcount is %i", blockcount);

        // now the pointer is at the end of the file, for each of the block, read it to data, reverse the pointer by 2, and write buffer to output.
        for (int i = 0; i < blockcount; i++)
        {

            fread(&buffer, sizeof(blocksize), 1, input);
            fseek(input, -2 * sizeof(blocksize), SEEK_CUR);
            fwrite(&buffer, sizeof(blocksize), 1, output);
        }
    }

    fclose(input);
    fclose(output);
}

int check_format(WAVHEADER header)
{
    // TODO #4
    // WAVEHEADER *h = malloc(sizeof(WAVEHEADER));
    // *h = header;

    // free (h)
    BYTE headercheck[] = {'W', 'A', 'V', 'E'};
    for (int i = 0; i < 4; i++)
    {
        if (header.format[i] != headercheck[i])
            return 0;
    }

    return 1;
}

int get_block_size(WAVHEADER header)
{
    // TODO #7
    int block_size = header.numChannels * header.bitsPerSample / 8;

    return block_size;
}
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#include "wav.h"

int check_format(WAVHEADER header);
int get_block_size(WAVHEADER header);

int main(int argc, char *argv[])
{
    // Ensure proper usage
    // TODO #1
    if (argc != 3)
    {
        printf("Usage: ./reverse input.wav output.wav\n");
        return 1;
    }
    // Open input file for reading
    // TODO #2

    // step1 create a pointer that point at the input/output file and initiate them with the argument value
    FILE *input = fopen(argv[1], "r");
    if (input == NULL)
    {
        printf("could not open input file\n");
        return 1;
    }

    // Read header
    // TODO #3

    // WAVHEADER wavheader = fread(&wavheader, sizeof(BYTE), 44, input);
    // This is wrong because the data structure is already include all the info of header. SO the
    WAVHEADER header;
    fread(&header, sizeof(WAVHEADER), 1, input);
    // Use check_format to ensure WAV format
    // TODO #4
    if (!check_format(header))
    {
        printf("unsupported format\n");
        return 2;
    }
    // Open output file for writing
    // TODO #5
    FILE *output = fopen(argv[2], "w");
    if (output == NULL)
    {
        printf("could not open output file\n");
    }
    // Write header to file
    // TODO #6
    fwrite(&header, sizeof(WAVHEADER), 1, output);

    // Use get_block_size to calculate size of block
    // TODO #7
    int blocksize = get_block_size(header);

    // Write reversed audio to file
    // TODO #8

    // create a buffer to story the each unit (aka blocksize) of reversed audio. The reversed buffer will be fread to buffer and fwrite to output file..
    BYTE buffer[blocksize];
    {
        // after fread the header, the pointer is at the beginging of audio date. find its location referred to the begining of the file.
        long starting = ftell(input);
        // move the pointer to the end of the file and find the relative location, then, find the block count.
        fseek(input, 0, SEEK_END);
        long ending = ftell(input);
        int blockcount = (ending - starting) / blocksize;
        // printf("starting is %li", starting );
        // printf("ending is %li", ending );

        // printf("blockcount is %i", blockcount);

        // now the pointer is at the end of the file, for each of the block, read it to data, reverse the pointer by 2, and write buffer to output.
        for (int i = 0; i < blockcount; i++)
        {

            fread(&buffer, sizeof(blocksize), 1, input);
            fseek(input, -2 * sizeof(blocksize), SEEK_CUR);
            fwrite(&buffer, sizeof(blocksize), 1, output);
        }
    }

    fclose(input);
    fclose(output);
}

int check_format(WAVHEADER header)
{
    // TODO #4
    // WAVEHEADER *h = malloc(sizeof(WAVEHEADER));
    // *h = header;

    // free (h)
    BYTE headercheck[] = {'W', 'A', 'V', 'E'};
    for (int i = 0; i < 4; i++)
    {
        if (header.format[i] != headercheck[i])
            return 0;
    }

    return 1;
}

int get_block_size(WAVHEADER header)
{
    // TODO #7
    int block_size = header.numChannels * header.bitsPerSample / 8;

    return block_size;
}