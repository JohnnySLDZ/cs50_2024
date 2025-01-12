#include <stdio.h>
#include <cs50.h>

int main(int argc, string argv[])
{
    for(int i = 0; i < argc; i++)
    {
        printf("%i: %s\n", i, argv[i]);
    }
    printf("%i spaces in the array\n", argc);

}
