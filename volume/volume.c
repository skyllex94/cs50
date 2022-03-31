// Modifies the volume of an audio file

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

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
    FILE *input = fopen(argv[1], "r");
    if (input == NULL)
    {
        printf("Could not open file.\n");
        return 1;
    }

    FILE *output = fopen(argv[2], "w");
    if (output == NULL)
    {
        printf("Could not open file.\n");
        return 1;
    }

    float factor = atof(argv[3]);

    // TODO: Copy header from input file to output file

    uint8_t *header = malloc(HEADER_SIZE);
    uint16_t *buffer = malloc(sizeof(input));

    for (uint8_t i = 0; i < HEADER_SIZE; i++)
    {
        fread(&header[i], sizeof(uint8_t), 1, input);
        // uint16_t buffer = *header;
        fwrite(&header[i], sizeof(uint8_t), 1, output);
        // fprintf(output, "This is CS50\n");
    }

    // TODO: Read samples from input file and write updated data to output file

    for (uint16_t i = HEADER_SIZE; i < sizeof(input); i++)
    {
        fread(&buffer[i], sizeof(uint16_t), 1, input);
        // uint16_t buffer = *header;
        fwrite(&buffer[i], sizeof(uint16_t), factor, output);
        // fprintf(output, "This is CS50\n");
    }

    free(buffer);
    free(header);
    // Close files
    fclose(input);
    fclose(output);
}
