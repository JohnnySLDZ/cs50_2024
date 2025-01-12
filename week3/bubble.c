#import <cs50.h>
#import <stdio.h>

int main(void)
{
    const int n = 7;
    int numbers[n] = {0,1,2,3,4,5,6};
    int counter;
    int swap = 0;
    //repeat n-1 times
    for(int i = 0; i < n-2; i++)
    {
    //     //For i from 0 to n-2
        for(int j = 0; j < n-1; j++)
        {
            //If numbers[i] and numbers[i+1] out of order
            if(numbers[j] > numbers[j+1])
            {
                //Swap them
                counter = numbers[j];
                numbers[j] = numbers[j+1];
                numbers[j+1]= counter;
                swap = 1;
            }
            //If no swaps quit
        }
        if(swap == 0)
        {
            printf("\nNo sorting needed\n");
            break;
        }
    }
    printf("{");
    for(int i = 0; i < n; i++)
    {
        if(i == n-1)
        {
            printf("%i", numbers[i]);
        }else
        {
            printf("%i,", numbers[i]);
        }

    }
    printf("}\n");
}
