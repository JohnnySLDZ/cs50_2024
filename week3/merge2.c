#include <stdio.h>

void merge(int start, int mid, int end, int array[]);
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
    int l = mid-start+1;
    int r = end-mid;
    int left[l];
    int right[r];
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

int main(void)
{
    const int n = 11;
    int array[n] ={0,1,2,3,4,5,6,7,8,9,10};
    merge_sort(0,n-1,array);
    for(int i = 0; i < n; i++)
    {
        printf("%i,", array[i]);
    }
}
