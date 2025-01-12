#include <cs50.h>
#include <stdio.h>

int main(void){

    int x = get_int("give me a number\n");
    int y = get_int("give me another number\n");
    if(x < y){
        printf("the number %i is less than %i\n", x, y);
    }else if(x > y){
        printf("the number %i is greater than %i\n", x, y);
    }else{
        printf("the number %i and the number %i are equal\n", x, y);
    }

}
