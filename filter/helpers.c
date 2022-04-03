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

    RGBTRIPLE temp[height][width];

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            temp[i][j] = image[i][j];

            float sum_blue = 0;
            float sum_green = 0;
            float sum_red = 0;

            for (int c = -1; c < 1; c++)
            {
                for (int v = -1; v < 1; v++)
                {
                    sum_blue += temp[i + c][j + v].rgbtBlue;
                    sum_green += temp[i + c][j + v].rgbtGreen;
                    sum_red += temp[i + c][j + v].rgbtRed;
                }
            }

            temp[i][j].rgbtBlue = round(sum_blue / 9);
            temp[i][j].rgbtGreen = round(sum_green / 9);
            temp[i][j].rgbtRed = round(sum_red / 9);

            image[i][j].rgbtBlue = temp[i][j].rgbtBlue;
            image[i][j].rgbtGreen = temp[i][j].rgbtGreen;
            image[i][j].rgbtRed = temp[i][j].rgbtRed;
        }
    }

    return;
}
