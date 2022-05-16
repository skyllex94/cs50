#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

int main(int argc, char *argv[])
{
    if (argc != 1)
    {
        printf("This is CS50\n");

        FILE *file = fopen(argv[1], "r");
        int block_size = 512;
        uint8_t buffer[block_size];
        char *filename = NULL;

        if (file == NULL)
        {
            return 1;
        }

        while (fread(buffer, sizeof(uint8_t), block_size, file) == block_size)
        {
            if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] & 0xf0) == 0xe0)
            {
                // printf("%c", buffer);
                sprintf(filename, "%03i.jpg", 2);

                // Open file to write the jpg data into
                uint8_t data[block_size];

                FILE *img = fopen(filename, "w");
                while (fwrite(data, sizeof(uint8_t), block_size, img) == block_size)
                {
                }
            }
            else
            {
                return 1;
            }
        }
    }
    else
    {
        printf("Usage: ./recover [flag] rawfile\n");
        return 1;
    }
}