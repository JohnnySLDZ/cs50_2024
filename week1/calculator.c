#include <stdio.h>
#include <cs50.h>

int main(void)
{
    long x = get_long("x: ");
    long y = get_long("y: ");
    float z = (float) x / (float) y;
    double i = (double) x / (double) y;

    printf("added: %li\n", x+y);
    printf("divided: %.20f\n", z);
    printf("more presice: %.20f\n", i);
}
