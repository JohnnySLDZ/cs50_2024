#include <stdio.h>
#include <cs50.h>

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
        n = get_int("How big is the wall gonna be?\n");
    }
    while(n < 1);
    return n;
}

void print_wall(int size)
{
    for(int i = 0; i < size; i++)
    {
        for(int j = 0; j < size+1; j++)
        {
            printf("#");
        }
        printf("\n");
    }
}
