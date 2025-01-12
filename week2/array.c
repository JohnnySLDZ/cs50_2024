#include <stdio.h>
#include <cs50.h>


float average(int length, int array[]);
const int N = 3;
int main(void)
{
    int scores[N];
    for(int i = 0; i < N; i++)
    {
        scores[i]= get_int("Score: ");
    }

    printf("The average is: %.2f\n", average(N, scores));

}

float average(int length, int array[])
{
    int sum = 0;
    for(int i = 0; i < length; i++)
    {
        sum += array[i];
    }
    return sum / (float) length;
}
