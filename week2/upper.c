#include <stdio.h>
#include <cs50.h>
#include <string.h>

int main(void)
{
    string s = get_string("Lower Case: ");
    for(int i = 0; i < strlen(s); i++)
    {
        if( s[i]>= 97 && s[i]<=122)
        {
            s[i]-=32;
        }
    }
    printf("Upper Case: %s\n", s);
}
