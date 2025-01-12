#include <cs50.h>
#include <math.h>
#include <stdio.h>

int main(void)
{
    long number = get_long("Number: ");

    int len = floor(log10(number)) + 1;
    int arrayNumber[len];

    for (int i = 0; i < len; i++)
    {
        arrayNumber[i] = number % 10;
        number /= 10;
    }

    int sum1 = 0, sum2 = 0, totalSum = 0;
    for (int i = 0; i < len; i++)
    {
        if (i % 2 != 0)
        {
            if ((arrayNumber[i] * 2) > 9)
            {
                sum1 += (arrayNumber[i] * 2) % 10;
                sum1 += (arrayNumber[i] * 2) / 10;
            }
            else
            {
                sum1 += arrayNumber[i] * 2;
            }
        }
        else
        {
            sum2 += arrayNumber[i];
        }
    }
    totalSum = sum1 + sum2;

    if (totalSum % 10 != 0)
    {
        printf("INVALID\n");
    }
    else if (len == 15 && (arrayNumber[len - 1] == 3 &&
                           (arrayNumber[len - 2] == 4 || arrayNumber[len - 2] == 7)))
    {
        printf("AMEX\n");
    }
    else if (len == 16 && arrayNumber[len - 1] == 5 &&
             (arrayNumber[len - 2] > 0 && arrayNumber[len - 2] < 6))
    {
        printf("MASTERCARD\n");
    }
    else if ((len == 13 || len == 16) && arrayNumber[len - 1] == 4)
    {
        printf("VISA\n");
    }
    else
    {
        printf("INVALID\n");
    }
}
