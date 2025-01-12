#include <stdio.h>
#include <cs50.h>

int main(void)
{
    int x = get_int("give me a number\n");
    switch(x)
    {
        case 1:
        printf("one\n");
        break;
        case 2:
        printf("two\n");
        break;
        case 3:
        printf("three\n");
        break;
        default:
        printf("Not the number required\n");
    }
    int y = get_int("give me another number\n");
    int z = (y > x) ? y : x;
    printf("z: %i\n", z);
}
