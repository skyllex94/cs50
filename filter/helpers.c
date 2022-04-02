#include <math.h>
#include <stdlib.h>

#include "helpers.h"

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int blue_color = round(image[i][j].rgbtBlue);
            int green_color = round(image[i][j].rgbtGreen);
            int red_color = round(image[i][j].rgbtRed);

            float average_color = (blue_color + green_color + red_color) / 3.0;

            image[i][j].rgbtBlue = round(average_color);
            image[i][j].rgbtGreen = round(average_color);
            image[i][j].rgbtRed = round(average_color);
        }
    }
    return;
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int blue_color = round(image[i][j].rgbtBlue);
            int green_color = round(image[i][j].rgbtGreen);
            int red_color = round(image[i][j].rgbtRed);

            int sepiaRed = round(.393 * red_color + .769 * green_color + .189 * blue_color);
            int sepiaGreen = round(.349 * red_color + .686 * green_color + .168 * blue_color);
            int sepiaBlue = round(.272 * red_color + .534 * green_color + .131 * blue_color);

            if (sepiaRed > 255)
            {
                sepiaRed = 255;
            }
            if (sepiaGreen > 255)
            {
                sepiaGreen = 255;
            }
            if (sepiaBlue > 255)
            {
                sepiaBlue = 255;
            }

            image[i][j].rgbtBlue = sepiaBlue;
            image[i][j].rgbtGreen = sepiaGreen;
            image[i][j].rgbtRed = sepiaRed;
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width / 2; j++)
        {
            RGBTRIPLE temp = image[i][j];

            image[i][j] = image[i][width - (j + 1)];
            image[i][width - (j + 1)] = temp;
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{

    // for (int i = 0; i < height; i++)
    // {
    //     for (int j = 0; j < width; j++)
    //     {
    //         RGBTRIPLE temp = image[i][j];
    //         for (int c = (i - 1); c < i)
    //     }
    // }
    return;
}
