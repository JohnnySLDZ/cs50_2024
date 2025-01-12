#include <stdio.h>

void swap(int *a, int *b);
int main(void)
{
    int x = 13;
    int y = 7;
    printf("x = %i\ny = %i\n\n", x, y);
    swap(&x, &y);
    printf("x = %i\ny = %i\n", x, y);
}

void swap(int *a, int *b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}
