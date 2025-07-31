#include "helpers.h"
#include <math.h>

#define NUM_COLORS 3

BYTE find_avg(unsigned int numbers_count, unsigned int numbers_arr[numbers_count])
{
    unsigned int numbers_sum = 0;
    float return_avg;

    for (int i = 0; i < numbers_count; i++)
    {
        numbers_sum += numbers_arr[i];
    }

    return_avg = (double) numbers_sum / (double) numbers_count;

    // return (unsigned int)round((double)(numbers_sum / numbers_count));
    return (BYTE) round(return_avg);
}

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            unsigned int colors[NUM_COLORS];
            colors[0] = image[i][j].rgbtBlue;
            colors[1] = image[i][j].rgbtGreen;
            colors[2] = image[i][j].rgbtRed;
            BYTE avg = find_avg(NUM_COLORS, colors);
            image[i][j].rgbtBlue = avg;
            image[i][j].rgbtGreen = avg;
            image[i][j].rgbtRed = avg;
        }
    }

    return;
}

void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            unsigned int sepiaRed = (unsigned int) round(0.393 * (double) image[i][j].rgbtRed +
                                                         0.769 * (double) image[i][j].rgbtGreen +
                                                         0.189 * (double) image[i][j].rgbtBlue);
            unsigned int sepiaGreen = (unsigned int) round(0.349 * (double) image[i][j].rgbtRed +
                                                           0.686 * (double) image[i][j].rgbtGreen +
                                                           0.168 * (double) image[i][j].rgbtBlue);
            unsigned int sepiaBlue = (unsigned int) round(0.272 * (double) image[i][j].rgbtRed +
                                                          0.534 * (double) image[i][j].rgbtGreen +
                                                          0.131 * (double) image[i][j].rgbtBlue);
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

            image[i][j].rgbtRed = sepiaRed;
            image[i][j].rgbtGreen = sepiaGreen;
            image[i][j].rgbtBlue = sepiaBlue;
        }
    }
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width / 2; j++)
        {
            RGBTRIPLE temp = image[i][j];
            image[i][j] = image[i][width - j - 1];
            image[i][width - j - 1] = temp;
        }
    }

    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    // Create a copy of image
    RGBTRIPLE copy[height][width];
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            copy[i][j] = image[i][j];
        }
    }

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            unsigned int avg_blue = 0;
            unsigned int avg_green = 0;
            unsigned int avg_red = 0;
            unsigned int num_pixels = 0;
            for (int k = i - 1; k <= i + 1 && k < height; k++)
            {
                if (k < 0)
                {
                    continue;
                }

                for (int l = j - 1; l <= j + 1 && l < width; l++)
                {
                    if (l < 0)
                    {
                        continue;
                    }

                    avg_blue += copy[k][l].rgbtBlue;
                    avg_green += copy[k][l].rgbtGreen;
                    avg_red += copy[k][l].rgbtRed;
                    num_pixels++;
                }
            }
            image[i][j].rgbtBlue = (unsigned int) round((double) avg_blue / (double) num_pixels);
            image[i][j].rgbtGreen = (unsigned int) round((double) avg_green / (double) num_pixels);
            image[i][j].rgbtRed = (unsigned int) round((double) avg_red / (double) num_pixels);
        }
    }

    return;
}
