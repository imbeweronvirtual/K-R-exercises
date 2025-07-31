// Modifies the volume of an audio file

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

typedef uint8_t BYTE;

// Number of bytes in .wav header
const int HEADER_SIZE = 44;

int main(int argc, char *argv[])
{
    // Check command-line arguments
    if (argc != 4)
    {
        printf("Usage: ./volume input.wav output.wav factor\n");
        return 1;
    }

    // Open files and determine scaling factor
    FILE *input = fopen(argv[1], "rb");
    if (input == NULL)
    {
        printf("Could not open file.\n");
        return 1;
    }

    FILE *output = fopen(argv[2], "wb");
    if (output == NULL)
    {
        printf("Could not open file.\n");
        return 1;
    }

    float factor = atof(argv[3]);

    // TODO: Copy header from input file to output file

    {
        BYTE header[HEADER_SIZE];
        if (fread(header, sizeof(header[0]), HEADER_SIZE, input) != HEADER_SIZE)
        {
            return 1;
        }
        if (fwrite(header, sizeof(header[0]), HEADER_SIZE, output) != HEADER_SIZE)
        {
            return 1;
        }
    }

    // TODO: Read samples from input file and write updated data to output file
    int16_t sample_buff;
    while (fread(&sample_buff, sizeof(sample_buff), 1, input) != 0)
    {
        sample_buff *= factor;

        fwrite(&sample_buff, sizeof(sample_buff), 1, output);
    }
    
    // Close files
    fclose(input);
    fclose(output);
}
