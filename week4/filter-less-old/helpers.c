#include "helpers.h"
#include <math.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    int average;
    for(int i = 0; i < height; i++)
    {
        for(int j = 0; j < width; j++)
        {
           average = (image[i][j].rgbtBlue + image[i][j].rgbtGreen + image[i][j].rgbtRed)/3;
           image[i][j].rgbtBlue = average;
           image[i][j].rgbtGreen = average;
           image[i][j].rgbtRed = average;
        }
    }
    return;
}
void mask(int height, int width, RGBTRIPLE image[height][width])
{
    int average;
    for(int i = 0; i < height; i++)
    {
        for(int j = 0; j < width; j++)
        {
           average = (image[i][j].rgbtBlue + image[i][j].rgbtGreen + image[i][j].rgbtRed)/3;
           if(average >= 255/2)
           {
            average = 255;
           }
           else
           {
            average = 0;
           }
           image[i][j].rgbtBlue = average;
           image[i][j].rgbtGreen = average;
           image[i][j].rgbtRed = average;
        }
    }
    return;
}
// rgbtBlue;
// rgbtGreen;
// rgbtRed;
// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    const int rgb = 3;
    float pixel[rgb];
    for(int i = 0; i < height; i++)
    {
        for(int j = 0; j < width; j++)
        {
            pixel[2] = (.272*image[i][j].rgbtRed) + (.534*image[i][j].rgbtGreen) + (.131*image[i][j].rgbtBlue);
            pixel[1] = (.349*image[i][j].rgbtRed) + (.686*image[i][j].rgbtGreen) + (.168*image[i][j].rgbtBlue);
            pixel[0] = (.393*image[i][j].rgbtRed) + (.769*image[i][j].rgbtGreen) + (.189*image[i][j].rgbtBlue);
            for(int k = 0; k < rgb; k++)
            {
                if(pixel[k]>255)
                {
                    pixel[k] = 255;
                }
                if((pixel[k]-floor(pixel[k]))>=.5)
                {
                    pixel[k] = floor(pixel[k])+1;
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
    for(int i = 0; i < height; i++)
    {
        merge_sort(0, width-1, image[i]);
    }
    return;
}
void merge_sort(int start, int end, RGBTRIPLE array[])
{
    if(end <= start)
    {
        return;
    }
    int mid = start+(end-start)/2;
    merge_sort(start, mid, array);
    merge_sort(mid+1,end,array);
    merge(start,mid,end,array);
}

void merge(int start, int mid, int end, RGBTRIPLE array[])
{
    int l = mid-start+1;
    int r = end-mid;
    RGBTRIPLE left[l];
    RGBTRIPLE right[r];
    int i,j,k;
    for(i= 0; i < l; i++)
    {
        left[i] = array[start+i];
    }
    for(j = 0; j < r; j++)
    {
        right[j] = array[mid+j+1];
    }
    i = 0;
    j = 0;
    k = start;
    while(k <= end)
    {
        if(j < r)
        {
            array[k]=right[j];
            k++;
            j++;
        }
        else
        {
            array[k]=left[i];
            k++;
            i++;
        }
    }
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    int total = 0;
    int avrgRed = 0;
    int avrgGreen = 0;
    int avrgBlue = 0;
    for(int i = 0; i < height; i++)
    {
        for(int j = 0; j < width; j++)
        {
            for(int k = i-1; k <=i+1 ; k++)
            {
                if(k < 0)
                {
                   continue;
                }
                else if(k>height-1)
                {
                    break;
                }
                for(int z = j-1; z <= j+1; z++)
                {
                    if(z < 0)
                    {
                        continue;
                    }
                    else if(z>width-1)
                    {
                        break;
                    }
                    avrgRed+= image[k][z].rgbtRed;
                    avrgGreen+= image[k][z].rgbtGreen;
                    avrgBlue+= image[k][z].rgbtBlue;
                    total++;
                }
            }
            avrgRed/=total;
            avrgGreen/=total;
           avrgBlue/=total;
           image[i][j].rgbtRed = (avrgRed > 255) ? 255 : avrgRed;
           image[i][j].rgbtGreen = (avrgGreen > 255) ? 255 : avrgGreen;
           image[i][j].rgbtBlue = (avrgBlue > 255) ? 255 : avrgBlue;
            avrgRed = 0;
            avrgGreen = 0;
            avrgBlue = 0;
           total=0;
        }
    }
    return;
}
