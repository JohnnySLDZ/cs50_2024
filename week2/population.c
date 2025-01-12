#include <stdio.h>
#include <cs50.h>

int llamasAtTheStart(void);
int llamasAtTheEnd(int startingSize);
void lifeAndDeath(int start, int finish);

int main(void)
{
    int startingSize = llamasAtTheStart();
    int endingSize = llamasAtTheEnd(startingSize);
    printf("start: %i\nend: %i\n", startingSize, endingSize);
    lifeAndDeath(startingSize, endingSize);
}

int llamasAtTheStart(void)
{
    int startingSize;
    do
    {
        startingSize = get_int("How many llamas are there? (the minimum are 9): ");
    }
    while (startingSize < 9);
    return startingSize;
}

int llamasAtTheEnd(int startingSize)
{
    int endingSize;
    do
    {
        endingSize = get_int("How many llamas are going to be at the end? (has to be more than the starting size): ");
    }
    while (endingSize <= startingSize);
    return endingSize;
}

void lifeAndDeath(int start, int finish)
{
    int llamas, born, death, years;
    llamas = start;
    years = 0;
    do
    {
        born = llamas/3;
        death = llamas/4;
        llamas = llamas + born - death;
        years++;
    }
    while(llamas < finish);
    printf("years: %i\n", years);
}
