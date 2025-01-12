#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <string.h>

string replace(string s);
int main(int argc, string argv[])
{
    if (argc == 2)
    {
        string message = argv[1];
        for (int i = 0, n = strlen(message); i < n; i++)
        {
            message[i] = tolower(message[i]);
        }
        printf("coded message: %s\n", replace(message));
    }
    else
    {
        printf("Inappropriate number of arguments, run the program again. Error Number:\n");
        return 1;
    }
}

string replace(string s)
{
    for (int i = 0, n = strlen(s); i < n; i++)
    {
        switch (s[i])
        {
            case 'a':
                s[i] = '6';
                break;
            case 'e':
                s[i] = '3';
                break;
            case 'i':
                s[i] = '1';
                break;
            case 'o':
                s[i] = '0';
                break;
            default:
                break;
        }
    }
    return s;
}
