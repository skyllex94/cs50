#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
typedef uint8_t BYTE;

int main(int argc, char *argv[])
{
    if (argc != 1)
    {
        printf("This is CS50\n");

        FILE *file = fopen(argv[1], "r");
        int block_size = 512;
        unsigned char buffer[block_size];

        char *filename = malloc(8 * sizeof(char));
        int image_counter = 0;

        FILE *img = NULL;
        // bool img_found = false;

        if (file == NULL)
        {
            return 1;
        }

        while (fread(buffer, sizeof(char), block_size, file))
        {
            if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] & 0xf0) == 0xe0)
            {
                sprintf(filename, "%03i.jpg", image_counter);
                image_counter++;

                img = fopen(filename, "w");
            }

            if (img != NULL)
            {
                fwrite(buffer, sizeof(char), block_size, img);
            }
        }
        free(filename);
        fclose(img);
        fclose(file);

        return 0;
    }
    else
    {
        printf("Usage: ./recover [flag] rawfile\n");
        return 1;
    }
}