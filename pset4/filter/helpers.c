#include "helpers.h"
#include <math.h>
#include <stdio.h>
// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    BYTE avg;  //defing average of size of byte
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            // Taking average of three colours for each pixel.
            avg = round((image[i][j].rgbtRed + image[i][j].rgbtGreen + image[i][j].rgbtBlue) / 3.0);
            // changing each image coloured pexel with average coloured pixel i.e converting into gray scale.
            image[i][j].rgbtRed = avg;
            image[i][j].rgbtGreen = avg;
            image[i][j].rgbtBlue = avg;
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    BYTE a, b, c;
    int  w = width / 2 ; //we just have to reflact half left to right and vise versa.
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < w; j++)
        {
            //Doing reflection by swaping.
            a = image[i][j].rgbtRed;
            b = image[i][j].rgbtGreen;
            c = image[i][j].rgbtBlue;
            image[i][j].rgbtRed = image[i][width - 1 - j].rgbtRed;
            image[i][j].rgbtGreen = image[i][width - 1 - j].rgbtGreen;
            image[i][j].rgbtBlue = image[i][width - 1 - j].rgbtBlue;
            image[i][width - 1 - j].rgbtRed = a;
            image[i][width - 1 - j].rgbtGreen = b;
            image[i][width - 1 - j].rgbtBlue = c;
        }
    }

    return;
}


// Blur image
typedef struct
{
    int rgbtRed;
    int rgbtBlue;
    int rgbtGreen;
}
pixelValue;
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE cimage[height][width]; //cimage : copy image
    //Defining a null image array 2d.
    for (int s = 0; s < height; s++)
    {
        for (int t = 0; t < width; t++)
        {
            cimage[s][t].rgbtRed = 0;
            cimage[s][t].rgbtGreen = 0;
            cimage[s][t].rgbtBlue = 0;
        }
    }
    pixelValue imsum;
    //initializing sum for all three clours.
    imsum.rgbtRed = 0;
    imsum.rgbtBlue = 0;
    imsum.rgbtGreen = 0;
    int count = 0; //count for keeping track for number of pixel to find average.
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            //these two loop will insure only 3X3 array of 9 pixel.
            for (int k = i - 1;  k <= i + 1; k++)
            {
                for (int l = j - 1; l <= j + 1; l++)
                {
                    if ((k >= 0 && k < height) && (l >= 0 && l < width))
                    {
                        imsum.rgbtRed += image[k][l].rgbtRed;
                        imsum.rgbtGreen += image[k][l].rgbtGreen;
                        imsum.rgbtBlue += image[k][l].rgbtBlue;
                        count++;
                    }
                }
            }
            cimage[i][j].rgbtRed = round(imsum.rgbtRed / (float)count);
            cimage[i][j].rgbtGreen = round(imsum.rgbtGreen / (float)count);
            cimage[i][j].rgbtBlue = round(imsum.rgbtBlue / (float)count);
            imsum.rgbtRed = 0;
            imsum.rgbtGreen = 0;
            imsum.rgbtBlue = 0;
            count = 0;
        }
    }
    //copying the blured image(cimage) into image.
    for (int m = 0; m < height; m++)
    {
        for (int n = 0; n < width; n++)
        {
            image[m][n] = cimage[m][n];
        }
    }
    return;
}

// Detect edges


void edges(int height, int width, RGBTRIPLE image[height][width])
{
    //convolution matrices in x and y direction.
    int Gx[3][3] = {{- 1, 0, 1}, {- 2, 0, 2}, {-1, 0, 1}};
    int Gy[3][3] = {{- 1, - 2, - 1}, {0, 0, 0}, {1, 2, 1}};
    RGBTRIPLE cimage[height][width];
    //Defining a null image array 2d.
    for (int s = 0; s < height; s++)
    {
        for (int t = 0; t < width; t++)
        {
            cimage[s][t].rgbtRed = 0;
            cimage[s][t].rgbtGreen = 0;
            cimage[s][t].rgbtBlue = 0;
        }
    }
    pixelValue imgx, imgy, G;
    //initaializing values.
    imgx.rgbtRed = 0;
    imgx.rgbtGreen = 0;
    imgx.rgbtBlue = 0;
    imgy.rgbtRed = 0;
    imgy.rgbtGreen = 0;
    imgy.rgbtBlue = 0;
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            for (int k = i - 1; k <= i + 1; k++)
            {
                for (int l = j - 1; l <= j + 1; l++)
                {
                    if ((k >= 0 && k < height) && (l >= 0 && l < width))
                    {
                        //multipying 3X3 pixel value to convolution matrix.
                        imgx.rgbtRed += image[k][l].rgbtRed * Gx[k - (i - 1)][l - (j - 1)];
                        imgx.rgbtGreen  += image[k][l].rgbtGreen * Gx[k - (i - 1)][l - (j - 1)];
                        imgx.rgbtBlue  += image[k][l].rgbtBlue * Gx[k - (i - 1)][l - (j - 1)];
                        imgy.rgbtRed += image[k][l].rgbtRed * Gy[k - (i - 1)][l - (j - 1)];
                        imgy.rgbtGreen  += image[k][l].rgbtGreen * Gy[k - (i - 1)][l - (j - 1)];
                        imgy.rgbtBlue  += image[k][l].rgbtBlue * Gy[k - (i - 1)][l - (j - 1)];
                    }
                    else
                    {
                        imgx.rgbtRed += 0;
                        imgx.rgbtGreen  += 0;
                        imgx.rgbtBlue  += 0;
                        imgy.rgbtRed += 0;
                        imgy.rgbtGreen  += 0;
                        imgy.rgbtBlue  += 0;
                    }
                }
            }
            //calculation final pixel value for each colour = sqrt(Gx^2 + Gy^2).
            G.rgbtRed = round(sqrt(pow(imgx.rgbtRed, 2) + pow(imgy.rgbtRed, 2)));
            G.rgbtGreen = round(sqrt(pow(imgx.rgbtGreen, 2) + pow(imgy.rgbtGreen, 2)));
            G.rgbtBlue = round(sqrt(pow(imgx.rgbtBlue, 2) + pow(imgy.rgbtBlue, 2)));
            //caping value maximum to 255.
            if (G.rgbtRed > 255)
            {
                cimage[i][j].rgbtRed = 255;
            }
            else
            {
                cimage[i][j].rgbtRed = G.rgbtRed;
            }
            if (G.rgbtGreen > 255)
            {
                cimage[i][j].rgbtGreen = 255;
            }
            else
            {
                cimage[i][j].rgbtGreen = G.rgbtGreen;
            }
            if (G.rgbtBlue > 255)
            {
                cimage[i][j].rgbtBlue = 255;
            }
            else
            {
                cimage[i][j].rgbtBlue = G.rgbtBlue;
            }
            imgx.rgbtRed = 0;
            imgx.rgbtGreen = 0;
            imgx.rgbtBlue = 0;
            imgy.rgbtRed = 0;
            imgy.rgbtGreen = 0;
            imgy.rgbtBlue = 0;
        }
    }
    // finally copying edge detected image into image
    for (int m = 0; m < height; m++)
    {
        for (int n = 0; n < width; n++)
        {
            image[m][n] = cimage[m][n];
        }
    }
    return;
}
