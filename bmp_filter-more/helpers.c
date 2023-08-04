#include "helpers.h"
#include <math.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int avg = (image[i][j].rgbtBlue + image[i][j].rgbtGreen + image[i][j].rgbtRed) / 3;
            image[i][j].rgbtBlue = avg;
            image[i][j].rgbtGreen = avg;
            image[i][j].rgbtRed = avg;
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE buffer;
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width / 2; j++)
        {
            buffer = image[i][j];
            image[i][j] = image[i][width - j];
            image[i][width - j] = buffer;
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{

    // for (int i=1; i < height-1; i++ )
    // {
    //     for (int j=1; j< width-1; j++)
    //     {
    //         int sumB=0;
    //         int sumG=0;
    //         int sumR=0;
    //         for (int k=-1; k<=1; k++)
    //         {
    //             for (int l=-1; l<=1; l++)
    //             {
    //                 sumB = sumR + image[i+k][j+l].rgbtBlue;
    //                 sumG = sumR + image[i+k][j+l].rgbtGreen;
    //                 sumR = sumR + image[i+k][j+l].rgbtRed;
    //             }

    //         }
    //         int avgB = sumB/9 ;
    //         int avgG = sumG/9 ;
    //         int avgR = sumR/9 ;

    //         image[i][j].rgbtBlue = avgB;
    //         image[i][j].rgbtGreen = avgG;
    //         image[i][j].rgbtRed = avgR;
    //     }
    // }
    RGBTRIPLE tmp[height][width];

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            //
            int sumB = 0;
            int sumG = 0;
            int sumR = 0;
            int boxcount = 0;
            for (int k = -1; k <= 1; k++)
            {
                if (i + k >= 0 && i + k <= height - 1)
                {
                    for (int l = -1; l <= 1; l++)
                    {
                        if (j + l >= 0 && j + l <= width - 1)
                        {
                            sumB = sumB + image[i + k][j + l].rgbtBlue;
                            sumG = sumG + image[i + k][j + l].rgbtGreen;
                            sumR = sumR + image[i + k][j + l].rgbtRed;
                            boxcount++;
                        }
                    }
                }
            }
            int avgB = sumB / boxcount;
            int avgG = sumG / boxcount;
            int avgR = sumR / boxcount;

            tmp[i][j].rgbtBlue = avgB;
            tmp[i][j].rgbtGreen = avgG;
            tmp[i][j].rgbtRed = avgR;
        }
    }
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image[i][j].rgbtBlue = tmp[i][j].rgbtBlue;
            image[i][j].rgbtGreen = tmp[i][j].rgbtGreen;
            image[i][j].rgbtRed = tmp[i][j].rgbtRed;
        }
    }

    return;
}

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE tmp[height][width];
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int GxB = 0;
            int GxG = 0;
            int GxR = 0;
            int GyB = 0;
            int GyG = 0;
            int GyR = 0;
            // int boxcount =0;
            for (int k = -1; k <= 1; k++)
            {
                if (i + k >= 0 && i + k <= height - 1)
                {
                    for (int l = -1; l <= 1; l++)
                    {
                        if (j + l >= 0 && j + l <= width - 1)
                        {

                            if (l == -1)
                            {
                                if (k == -1 || k == 1)
                                {
                                    GxB = GxB + image[i + k][j + l].rgbtBlue * (-1);
                                    GxG = GxG + image[i + k][j + l].rgbtGreen * (-1);
                                    GxR = GxR + image[i + k][j + l].rgbtRed * (-1);
                                }
                                if (k == 0)
                                {
                                    GxB = GxB + image[i + k][j + l].rgbtBlue * (-2);
                                    GxG = GxG + image[i + k][j + l].rgbtGreen * (-2);
                                    GxR = GxR + image[i + k][j + l].rgbtRed * (-2);
                                }
                            }

                            if (l == 1)
                            {
                                if (k == -1 || k == 1)
                                {
                                    GxB = GxB + image[i + k][j + l].rgbtBlue * (1);
                                    GxG = GxG + image[i + k][j + l].rgbtGreen * (1);
                                    GxR = GxR + image[i + k][j + l].rgbtRed * (1);
                                }
                                if (k == 0)
                                {
                                    GxB = GxB + image[i + k][j + l].rgbtBlue * (+2);
                                    GxG = GxG + image[i + k][j + l].rgbtGreen * (+2);
                                    GxR = GxR + image[i + k][j + l].rgbtRed * (+2);
                                }
                            }

                            if (k == -1)
                            {
                                if (l == -1 || l == 1)
                                {
                                    GyB = GyB + image[i + k][j + l].rgbtBlue * (-1);
                                    GyG = GyG + image[i + k][j + l].rgbtGreen * (-1);
                                    GyR = GyR + image[i + k][j + l].rgbtRed * (-1);
                                }
                                if (l == 0)
                                {
                                    GyB = GyB + image[i + k][j + l].rgbtBlue * (-2);
                                    GyG = GyG + image[i + k][j + l].rgbtGreen * (-2);
                                    GyR = GyR + image[i + k][j + l].rgbtRed * (-2);
                                }
                            }

                            if (k == 1)
                            {
                                if (l == -1 || l == 1)
                                {
                                    GyB = GyB + image[i + k][j + l].rgbtBlue * (1);
                                    GyG = GyG + image[i + k][j + l].rgbtGreen * (1);
                                    GyR = GyR + image[i + k][j + l].rgbtRed * (1);
                                }
                                if (l == 0)
                                {
                                    GyB = GyB + image[i + k][j + l].rgbtBlue * (+2);
                                    GyG = GyG + image[i + k][j + l].rgbtGreen * (+2);
                                    GyR = GyR + image[i + k][j + l].rgbtRed * (+2);
                                }
                            }
                        }
                    }
                }
            }
            int edgeB = sqrt(GxB * GxB + GyB * GyB);
            int edgeG = sqrt(GxG * GxG + GyG * GyG);
            int edgeR = sqrt(GxR * GxR + GyR * GyR);
            if (edgeB > 255)
            {
                edgeB = 255;
            }
            if (edgeG > 255)
            {
                edgeG = 255;
            }
            if (edgeR > 255)
            {
                edgeR = 255;
            }

            tmp[i][j].rgbtBlue = edgeB;
            tmp[i][j].rgbtGreen = edgeG;
            tmp[i][j].rgbtRed = edgeR;
        }
    }

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image[i][j].rgbtBlue = tmp[i][j].rgbtBlue;
            image[i][j].rgbtGreen = tmp[i][j].rgbtGreen;
            image[i][j].rgbtRed = tmp[i][j].rgbtRed;
        }
    }

    return;
}
