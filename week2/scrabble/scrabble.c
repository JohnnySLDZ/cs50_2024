#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <string.h>

const int letters = 26;
char alphabet[letters] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z'};
int points[letters + 1] = {1, 3, 3, 2, 1, 4, 2, 4, 1, 8, 5, 1, 3, 1, 1, 3, 10, 1, 1, 1, 1, 4, 4, 8, 4, 10, 0};

int getPoints(string s);

int main(void)
{
    string player1 = get_string("Player 1: ");
    string player2 = get_string("Player 2: ");

    int p1points = getPoints(player1);
    int p2points = getPoints(player2);

    if (p1points > p2points)
    {
        printf("Player 1 wins!");
    }
    else if (p1points < p2points)
    {
        printf("Player 2 wins!");
    }
    else
    {
        printf("Tie!");
    }
}

int getPoints(string s)
{
    int index;
    int pointSum = 0;
    for (int i = 0, n = strlen(s); i < n; i++)
    {
        index = letters;
        for (int j = 0; j < letters; j++)
        {
            if (toupper(s[i]) == alphabet[j])
            {
                index = j;
                break;
            }
        }
        pointSum += points[index];
    }
    return pointSum;
}
