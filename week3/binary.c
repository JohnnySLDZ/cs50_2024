#import <cs50.h>
#import <stdio.h>

void binary_search(int target, int start, int end, int array[]);

int main(void)
{
    const int size = 8;
    int numbers[size] = {1,2,3,4,5,6,7,8};
    int value = get_int("Number: ");
    binary_search(value, 0, size-1, numbers);
}

void binary_search(int target, int start, int end, int array[])
{
    int mid = start+(end-start)/2;
    if(start >= end && target != array[mid])
    {
        printf("not found :(\n");
        return;
    }
    else if(target == array[mid])
    {
        printf("found: numbers[%i] = %i\n", mid, target);
        return;
    }
    else if(target < array[mid])
    {
        binary_search(target, start, mid, array);
    }
    else if(target > array[mid])
    {
        binary_search(target, mid+1, end, array);
    }
}
