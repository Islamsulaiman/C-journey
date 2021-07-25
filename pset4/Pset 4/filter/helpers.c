#include "helpers.h"
#include <math.h>
#include <stdio.h>

// Convert image to grayscale


void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int row = 0; row < height; row++)
    {
        for (int col = 0; col < width; col++)
        {
            float avg = (image[row][col].rgbtRed + image[row][col].rgbtGreen + image[row][col].rgbtBlue) / 3.00 ;
            int agrv = round(avg);
            image[row][col].rgbtRed = agrv;
            image[row][col].rgbtGreen = agrv;
            image[row][col].rgbtBlue = agrv;
        }
    }

    return;
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    for (int row = 0; row < height; row++)
    {
        for (int col = 0; col < width; col++)
        {
            int red = round((.393 * image[row][col].rgbtRed) + (.769 * image[row][col].rgbtGreen) + (.189 * image[row][col].rgbtBlue));
            int green = round((.349 * image[row][col].rgbtRed) + (.686 * image[row][col].rgbtGreen) + (.168 * image[row][col].rgbtBlue));
            int blue = round((.272 * image[row][col].rgbtRed) + (.534 * image[row][col].rgbtGreen) + (.131 * image[row][col].rgbtBlue));

            image[row][col].rgbtRed = (red > 255) ? 255 : red;  //the syntax means set the arg on the right to red, if red more than 255 then red = 255 , else red is the same.
            image[row][col].rgbtGreen = (green > 255) ? 255 : green;
            image[row][col].rgbtBlue = (blue > 255) ? 255 : blue;
        }
    }

    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    for (int row = 0; row < height; row++)
    {
        for (int col = 0; col < (width / 2); col++)  //deviding by 2 because we are setting two pixels at the same time in the row
        {

            BYTE tempRed = image[row][col].rgbtRed;
            BYTE tempGreen = image[row][col].rgbtGreen;
            BYTE tempblue = image[row][col].rgbtBlue;

            image[row][col].rgbtRed = image[row][width - col - 1].rgbtRed;
            image[row][col].rgbtGreen = image[row][width - col - 1].rgbtGreen;
            image[row][col].rgbtBlue = image[row][width - col - 1].rgbtBlue;

            image[row][width - col - 1].rgbtRed = tempRed;
            image[row][width - col - 1].rgbtGreen = tempGreen;
            image[row][width - col - 1].rgbtBlue = tempblue;

        }
    }
    return;
}




// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE temp[height][width];

    for (int row = 0; row < height; row++)
    {
        for (int col = 0; col < width; col++)
        {
            float n = 0.00;              //no. of pixels exists to get the avg.
            int totRed = 0;         //total red for the existing pixels
            int totGreen = 0;       //total green for the existing pixels
            int totBlue = 0;        //total blue for the existing pixels

            //loop to get the surronding pixels if there is
            for (int i = -1; i < 2; i++)
            {
                for (int j = -1; j < 2; j++)
                {


                    if (col + j < 0 || row + i < 0 || col + j > width - 1 || row + i > height - 1)

                        continue;


                    totRed += image[row + i][col + j].rgbtRed;
                    totGreen += image[row + i][col + j].rgbtGreen;
                    totBlue += image[row + i][col + j].rgbtBlue;
                    n++;
                    // printf("totRed: %i, totGreen: %i, totBlue: %i, n: %i\n",totRed,totGreen,totBlue,n);

                }
            }

            temp[row][col].rgbtRed = round(totRed / n);
            temp[row][col].rgbtGreen = round(totGreen / n);
            temp[row][col].rgbtBlue = round(totBlue / n);
        }
    }


    for (int row = 0; row < height; row++)
    {
        for (int col = 0; col < width; col++)
        {
            image[row][col].rgbtRed = temp[row][col].rgbtRed;
            image[row][col].rgbtGreen = temp[row][col].rgbtGreen;
            image[row][col].rgbtBlue = temp[row][col].rgbtBlue;
        }
    }
}