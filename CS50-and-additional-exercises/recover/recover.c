#include <stdio.h>
#include <stdlib.h>

typedef __uint8_t BYTE;

FILE *create_file(unsigned int foto_count);

int main(int argc, char *argv[])
{
    // Check if executed right
    if (argc != 2)
    {
        printf("Execute the program: ./recover file-name.raw\n");
        return 1;
    }

    // Check if file exists
    FILE *input_file = fopen(argv[1], "r");
    if (input_file == NULL)
    {
        printf("Could not open the file\n");
        return 1;
    }

    // Initialize pointer
    FILE *output_file = NULL;
    unsigned int foto_count = 0;
    // Initialize buffer
    BYTE buff[512];

    // Read 512 bytes(1 block) per cycle
    while (fread(buff, sizeof(BYTE), 512, input_file))
    {
        // Check if we're at the start of the foto
        if (buff[0] == 0xff && buff[1] == 0xd8 && buff[2] == 0xff &&
            (buff[3] >= 0xe0 && buff[3] <= 0xef))
        {
            // If we had other foto close it because we found a new one
            if (output_file != NULL)
            {
                fclose(output_file);
            }

            // Create file with a name "###.jpg"
            output_file = create_file(foto_count);
            // Write this "start" block to file
            fwrite(buff, sizeof(BYTE), 512, output_file);
            // Update count
            foto_count++;
        }
        else
        {
            // If we have opened file it means that we read the foto now
            if (output_file != NULL)
            {
                fwrite(buff, sizeof(BYTE), 512, output_file);
            }
            else
            {
                continue;
            }
        }
    }

    fclose(input_file);
    fclose(output_file);
}

FILE *create_file(unsigned int foto_count)
{
    char buff[20];

    if (foto_count < 10)
    {
        sprintf(buff, "00%u.jpg", foto_count);
    }
    else if (foto_count < 100)
    {
        sprintf(buff, "0%u.jpg", foto_count);
    }
    else
    {
        sprintf(buff, "%u.jpg", foto_count);
    }

    FILE *ptr = fopen(buff, "w");
    return ptr;
}
