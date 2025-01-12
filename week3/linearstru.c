#import <cs50.h>
#import <stdio.h>
#import <string.h>

//creating a person type of data
typedef struct
{
    string name;
    string number;
}
person;

int main(void)
{
    //array with type person variables
    const int n = 3;
    person people[n];

    people[0].name = "Josh";
    people[0].number = "0424-944-6633";
    people[1].name = "Jorge";
    people[1].number = "0424-844-8394";
    people[2].name = "Juan";
    people[2].number = "0424-853-0846";

    //example of a linear search
    string personName = get_string("Name: ");
    for(int i = 0; i < n; i++)
    {
        printf("Number of operation %i\n", i+1);
        if(strcmp(people[i].name, personName)==0)
        {
            printf("Found\n");
            printf("Phone number of %s: %s\n", people[i].name, people[i].number);
            return 0;
        }
    }
    printf("Not Found\n");
}
