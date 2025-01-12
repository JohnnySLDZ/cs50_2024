#include <cs50.h>
#include <stdio.h>

int get_size(void);
void print_wall(int size);

int main(void)
{
    int num = get_size();
    print_wall(num);
}

int get_size(void)
{
    int n;
    do
    {
        n = get_int("Height: ");
    }
    while (n < 1 || n > 8);
    return n;
}

void print_wall(int size)
{
    for (int i = 0; i < size; i++)
    {
        for (int j = size - 1 - i; j > 0; j--)
        {
            printf(" ");
        }
        for (int k = 0; k < i + 1; k++)
        {
            printf("#");
        }
        printf("  ");
        for (int z = 0; z < i + 1; z++)
        {
            printf("#");
        }
        printf("\n");
    }
}
