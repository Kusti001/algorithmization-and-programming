#define GETRANDOM(min,max) \
((rand()%(int)(((max+1)-(min)))+(min))
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define PRINT_INT(var)\
printf(#var "=%d " ,var)

time_t curtime;

int main(void) {


// #var - имя переменной

int num = 5;
    PRINT_INT(num); // num = 5

    return 0;



}