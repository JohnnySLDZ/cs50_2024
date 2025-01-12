#include <cs50.h>
#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <string.h>

void get_words(string s, int *words, int *letters, int *sentences);
double average(int number, int words);

int main(void)
{
    string text = get_string("Text: ");
    int w = 1;
    int l = 0;
    int s = 0;

    get_words(text, &w, &l, &s);

    double L = average(l, w);
    double S = average(s, w);
    int index = round(0.0588 * L - 0.296 * S - 15.8);

    if (index < 1)
    {
        printf("Before Grade 1\n");
    }
    else if (index > 16)
    {
        printf("Grade 16+\n");
    }
    else
    {
        printf("Grade %i\n", index);
    }
}

void get_words(string s, int *words, int *letters, int *sentences)
{
    for (int i = 0; i < strlen(s); i++)
    {
        if (s[i] == ' ')
        {
            (*words)++;
        }
        else if (isalpha(s[i]))
        {
            (*letters)++;
        }
        else if (s[i] == '.' || s[i] == '!' || s[i] == '?')
        {
            (*sentences)++;
        }
    }
}

double average(int number, int words)
{
    double x = (double) number / (double) words * 100;
    return x;
}
