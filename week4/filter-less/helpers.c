#include "helpers.h"
#include <math.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    int average;
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            average =
                round((image[i][j].rgbtBlue + image[i][j].rgbtGreen + image[i][j].rgbtRed) / 3.0);
            image[i][j].rgbtBlue = average;
            image[i][j].rgbtGreen = average;
            image[i][j].rgbtRed = average;
        }
    }
    return;
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    const int rgb = 3;
    float pixel[rgb];
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            pixel[2] = (.272 * image[i][j].rgbtRed) + (.534 * image[i][j].rgbtGreen) +
                       (.131 * image[i][j].rgbtBlue);
            pixel[1] = (.349 * image[i][j].rgbtRed) + (.686 * image[i][j].rgbtGreen) +
                       (.168 * image[i][j].rgbtBlue);
            pixel[0] = (.393 * image[i][j].rgbtRed) + (.769 * image[i][j].rgbtGreen) +
                       (.189 * image[i][j].rgbtBlue);
            for (int k = 0; k < rgb; k++)
            {
                if (pixel[k] > 255)
                {
                    pixel[k] = 255;
                }
                if ((pixel[k] - floor(pixel[k])) >= .5)
                {
                    pixel[k] = floor(pixel[k]) + 1;
                }
            }
            image[i][j].rgbtRed = (int) pixel[0];
            image[i][j].rgbtGreen = (int) pixel[1];
            image[i][j].rgbtBlue = (int) pixel[2];
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        RGBTRIPLE temp;
        for (int j = 0; j < width / 2; j++)
        {
            temp = image[i][j];
            image[i][j] = image[i][width - j - 1];
            image[i][width - j - 1] = temp;
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    float total = 0.0;
    float avrgRed = 0;
    float avrgGreen = 0;
    float avrgBlue = 0;

    RGBTRIPLE temp[height][width];

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            temp[i][j] = image[i][j];
        }
    }
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            for (int k = i - 1; k <= i + 1; k++)
            {
                if (k < 0)
                {
                    continue;
                }
                else if (k > height - 1)
                {
                    break;
                }
                for (int z = j - 1; z <= j + 1; z++)
                {
                    if (z < 0)
                    {
                        continue;
                    }
                    else if (z > width - 1)
                    {
                        break;
                    }
                    avrgRed += temp[k][z].rgbtRed;
                    avrgGreen += temp[k][z].rgbtGreen;
                    avrgBlue += temp[k][z].rgbtBlue;
                    total++;
                }
            }
            avrgRed /= total;
            avrgGreen /= total;
            avrgBlue /= total;

            image[i][j].rgbtRed = (avrgRed > 255) ? 255 : round(avrgRed);
            image[i][j].rgbtGreen = (avrgGreen > 255) ? 255 : round(avrgGreen);
            image[i][j].rgbtBlue = (avrgBlue > 255) ? 255 : round(avrgBlue);
            avrgRed = 0;
            avrgGreen = 0;
            avrgBlue = 0;
            total = 0;
        }
    }
    return;
}
