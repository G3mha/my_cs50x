#include "helpers.h"
#include <math.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < width; i++)
    {
        for (int j = 0; j < height; j++)
        {
            // Get the average intensity of the 3 colors
            int GRAY = round((image[i][j].rgbtBlue + image[i][j].rgbtGreen + image[i][j].rgbtRed) / 3.0);

            // Apply the average to all colors, therefore getting gray
            image[i][j].rgbtBlue = GRAY;
            image[i][j].rgbtGreen = GRAY;
            image[i][j].rgbtRed = GRAY;
        }
    }

    // We are in a void, so returns nothing
    return;
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            // For each element, substitutes the original RGB color to a sepiaRGB color grading
            int redSEPIA = round(.393 * image[i][j].rgbtRed + .769 * image[i][j].rgbtGreen + .189 * image[i][j].rgbtBlue);
            int greenSEPIA = round(.349 * image[i][j].rgbtRed + .686 * image[i][j].rgbtGreen + .168 * image[i][j].rgbtBlue);
            int blueSEPIA = round(.272 * image[i][j].rgbtRed + .534 * image[i][j].rgbtGreen + .131 * image[i][j].rgbtBlue);
            image[i][j].rgbtRed = fmin(255, redSEPIA);
            image[i][j].rgbtGreen = fmin(255, greenSEPIA);
            image[i][j].rgbtBlue = fmin(255, blueSEPIA);
        }
    }

    // We are in a void, so returns nothing
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE filler; // initialize the variable that will be used just to copy and paste data through the loop
    for (int i = 0; i < height; i++) // Nest loop going through all rows, and every column that is less than half of the width
    {
        for (int j = 0; j < width / 2; j++)
        {
            // Change pixels on opposite sides (horizontal)
            filler = image[i][j];
            image[i][j] = image[i][width - j - 1];
            image[i][width - j - 1] = filler;
        }
    }

    // We are in a void, so returns nothing
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE temporary[height][width]; // var that will serve as a placeholder
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            // Initializing the average RGB variables
            int sumBLUE = 0;
            int sumRED = 0;
            int sumGREEN = 0;
            float n = 0.0; // amount of pixels in the image

            // Nested loop
            for (int x = -1; x < 2; x++)
            {
                for (int y = -1; y < 2; y++)
                {
                    if (i + x < 0 || i + x > height - 1 || j + y < 0 || j + y > width - 1)
                    {
                    }
                    else
                    {
                        sumBLUE += image[i + x][j + y].rgbtBlue;
                        sumGREEN += image[i + x][j + y].rgbtGreen;
                        sumRED += image[i + x][j + y].rgbtRed;
                        n++; // counting the pixels
                    }
                }
            }

            // Setting the new values for each pixel
            temporary[i][j].rgbtBlue = round(sumBLUE / n);
            temporary[i][j].rgbtGreen = round(sumGREEN / n);
            temporary[i][j].rgbtRed = round(sumRED / n);
        }
    }

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image[i][j].rgbtBlue = temporary[i][j].rgbtBlue;
            image[i][j].rgbtRed = temporary[i][j].rgbtRed;
            image[i][j].rgbtGreen = temporary[i][j].rgbtGreen;
        }
    }
    // We are in a void, so returns nothing
    return;
}
