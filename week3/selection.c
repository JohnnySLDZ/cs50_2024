#import <cs50.h>
#import <stdio.h>

int main(void)
{
    const int n = 7;
    int numbers[n] = {8,2,4,2,2,0,1};
    int currentNum;
    int index;
    int limit = 0;
    //finds the smallest number and place it in its place, n-1 cause theres no more numbers to compare the last one
    for(int j = 0; j < n-1; j++)
    {
        //finds the smallest number among the array
        for(int i = n-1; i >= limit; i--)
        {
            if(i == n-1)
            {
                if(numbers[i] > numbers[i-1])
                {
                    currentNum = numbers[i-1];
                    index = i-1;
                }
                else if(numbers[i] <= numbers[i-1])
                {
                    currentNum = numbers[i];
                    index = i;
                }
            }else
            {
                if(numbers[i] >= currentNum)
                {
                    continue;
                }
                else if(numbers[i] < currentNum)
                {
                    currentNum = numbers[i];
                    index = i;
                }
            }
        }
        //swaps the smallest number with the one thats in the first position
        numbers[index]=numbers[limit];
        numbers[limit]= currentNum;

        //reduces the loop that finds the smallest in order to not sort the ones that are already sorted
        limit++;
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
