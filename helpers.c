#include "helpers.h"

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    float blue, red, green;
    unsigned rgb_average;

    for (int i = 0; i < height; i++)
    {
        for(int j = 0; j < width; j++)
        {
            red = image[i][j].rgbtRed;
            blue = image[i][j].rgbtBlue;
            green = image[i][j].rgbtGreen;

            rgb_average = round((red + blue + green)/3);

            image[i][j].rgbtRed = rgb_average;
            image[i][j].rgbtBlue = rgb_average;
            image[i][j].rgbtGreen = rgb_average;
        }
    }

    return;
}


// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE (*pixel_buffer) = calloc(1, sizeof(RGBTRIPLE));

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < (width / 2); j++)
        {
            *pixel_buffer = image[i][width - 1 - j];
            image[i][width - 1 - j] = image[i][j];
            image[i][j] = *pixel_buffer;
        }
    }

    // Free memory
    free(pixel_buffer);

    return;
}


// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    float sum_blue, sum_green, sum_red, count;
    RGBTRIPLE (*image_buffer)[width] = calloc(height, width * sizeof(RGBTRIPLE));

    for (int line = 0; line < height; line++)
    {
        for (int column = 0; column < width; column++)
        {
            sum_blue = 0;
            sum_green = 0;
            sum_red = 0;
            count = 0;

            for (int i = -1; i <= 1; i++)
            {
                for (int j = -1; j <= 1; j++)
                {
                    if (((line + i) >= 0) && ((line + i) < height) &&
                        ((column + j) >= 0) && ((column + j) <  width))
                    {
                        sum_blue += image[line + i][column + j].rgbtBlue;
                        sum_green += image[line + i][column + j].rgbtGreen;
                        sum_red += image[line + i][column + j].rgbtRed;
                        count ++;
                    }

                    if ((line == height - 1) && (column == width - 1))
                    {
                        // printf("line: %i    column: %i\nred: %i    blue: %i     green: %i\ncount: %i\n\n", line, column, sum_red, sum_blue, sum_green, count);
                    }
                }
            }

            image_buffer[line][column].rgbtBlue = round(sum_blue / count);
            image_buffer[line][column].rgbtGreen = round(sum_green / count);
            image_buffer[line][column].rgbtRed = round(sum_red / count);
        }
    }

    for (int i = 0; i < height; i++)
    {
        for(int j = 0; j < width; j++)
        {
            image[i][j].rgbtBlue = image_buffer[i][j].rgbtBlue;
            image[i][j].rgbtGreen = image_buffer[i][j].rgbtGreen;
            image[i][j].rgbtRed = image_buffer[i][j].rgbtRed;
        }
    }

    // Free memory
    free (image_buffer);
    return;
}

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    return;
}
