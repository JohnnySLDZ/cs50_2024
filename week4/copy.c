#include <ctype.h>//For the toupper() function
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void)
{
    char *s = "qlq";
    int n = strlen(s);
    char *t = malloc(n+1);
    if(t == NULL)
    {
        return 4;
    }
    // for(int i = 0; i <= n; i++)
    // {
    //     t[i] = s[i];
    // }
    strcpy(t, s);
    if(strlen(t) > 0)
    {
       t[0] = toupper(t[0]);
    }
    printf("%s\n", s);
    printf("%s\n", t);
    free(t);
    return 0;
}
