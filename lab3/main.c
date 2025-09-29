
#include <stdio.h>
int a;
int val = 100;



int main(void){
    printf("ваш внутренний возраст: %d\n", 11);
    return 0;
}

/* стек: вызов fun() -> создание x, создание y -> вызов swap() -> создание t, замена указателей местами -> выход из swap -> выход из fun(). */
