#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char cypher(int key, int first_value, char value);

int main(int argc, string argv[])
{
    if (argc != 2)
    {
        printf("Not the correct input at the command line\n");
        return 1;
    }
    for (int i = 0; i < strlen(argv[1]); i++)
    {
        if (!isdigit(argv[1][i]))
        {
            printf("Not an int\n");
            return 1;
        }
    }
    int k = atoi(argv[1]);
    if (k <= 0)
    {
        printf("Invalid value\n");
        return 1;
    }

    string text = get_string("plaintext: ");
    int n = strlen(text);

    char cypher_text[n + 1];
    cypher_text[n] = '\0';

    for (int i = 0; i < n; i++)
    {
        if (isalpha(text[i]))
        {
            if (isupper(text[i]))
            {
                cypher_text[i] = cypher(k, 65, text[i]);
            }
            else if (islower(text[i]))
            {
                cypher_text[i] = cypher(k, 97, text[i]);
            }
        }
        else
        {
            cypher_text[i] = text[i];
        }
    }
    printf("ciphertext: %s\n", cypher_text);
}

char cypher(int key, int first_value, char value)
{
    char c = ((value - first_value + key) % 26) + first_value;
    return c;
}
