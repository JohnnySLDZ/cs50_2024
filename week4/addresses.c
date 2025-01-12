#include <stdio.h>
#include <string.h>
#include <stdlib.h>
int main(void)
{
    int n = 13;
    int *p = &n;
    int *x;

    x = malloc(sizeof(int));
    *x = 15;
    printf("%i\n\n", *x);
    char *s = "qlq";
    printf("%p\n", p);
    printf("%i\n\n", *p);

    printf("%p\n\n", s);
    for(int i = 0; i < strlen(s)+1; i++)
    {
        printf("%c\n", *(s+i));
    }
    printf("\n");
    for(int i = 0; i < strlen(s)+1; i++)
    {
        printf("%p\n", s+i);
    }
    free(x);
}
