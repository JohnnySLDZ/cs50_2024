#import <stdio.h>
#import <cs50.h>

void merge_sort(int start, int end, int array[]);
void merge(int start, int mid, int end, int array[]);
void print(int n, int array[]);


int main(void)
{
    const int n = 11;
    int array[n] = {6,4,8,10,7,2,0,3,5,9,1};
    // int tam = sizeof(A)/sizeof(A[0]);
    // sort(numbers);
    //If only one number
    //Quit
    //Else
    //Sort left half of numbers
    // Sort right half of numbers
    // Merge sorted halves
    merge_sort(0, n-1, array);
}

void merge_sort(int start, int end, int array[])
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

void merge(int start, int mid, int end, int array[])
{
    int left_length = mid-start+1;
    int right_length = end-mid;
    int left[left_length];
    int right[right_length];
    printf("(%i,%i,%i)\n",start,mid,end);
    print(end+1,array);
    int i,j,k;
    for(i = 0; i < left_length; i++)
    {
        left[i] = array[start+i];
    }
    print(left_length,left);
    for(j = 0; j < right_length; j++)
    {
        right[j] = array[mid+j+1];
    }
    print(right_length,right);
    i = 0;
    j = 0;
    k = start;
    while(k <= end)
    {
        if(i < left_length && left[i]<right[j] && j < right_length)
        {
            array[k] = left[i];
            i++;
        }
        else if(j < right_length && left[i] >= right[j] && i < left_length)
        {
            array[k] = right[j];
            j++;
        }
        else if(i == left_length && j < right_length)
        {
            array[k] = right[j];
            j++;
        }
        else if(j == right_length && i < left_length)
        {
            array[k] = left[i];
            i++;
        }
        k++;
    }
    printf("\n");
    print(end+1,array);
}
void print(int n, int array[])
{
    printf("{");
    for(int i = 0; i < n; i++)
    {
        if(i == n-1)
        {
            printf("%i",array[i]);
        }
        else
        {
            printf("%i,",array[i]);
        }

    }
    printf("}\n");
}
