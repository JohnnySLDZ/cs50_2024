#include <stdio.h>
#include <cs50.h>

float average(int array[], int number);
int total(int array[], int number);

int main(void)
{
    int weeks = get_int("How many weeks have you spent in cs50? ");
    int hours[weeks];
    for(int i = 0; i < weeks; i++)
    {
        hours[i] = get_int("how many hours you spent in week %i? ", i+1);
    }
    for(int i = 0; i < weeks; i++)
    {
        printf("Week number %i: %i hours\n", i+1, hours[i]);
    }
    char result;
    do
    {
        result = get_char("Press A for the average of hours or press T for the total of hours\n");
    }
    while(result != 'A' && result != 'T' && result != 't' && result != 'a');
    if(result == 'A' || result == 'a')
    {
        printf("The average of hours is: %.2f hours per week\n", average(hours,weeks));
        // printf("Do you want the total?");
    }
    else
    {
        printf("The total of hours is: %i hours\n", total(hours,weeks));
    }
}

float average(int array[], int number)
{
    float average = 0;
    for(int i =0; i < number; i++)
    {
        average+=array[i];
    }
    return average/number;
}
int total(int array[], int number)
{
    int total = 0;
    for(int i =0; i < number; i++)
    {
        total+=array[i];
    }
    return total;

}
