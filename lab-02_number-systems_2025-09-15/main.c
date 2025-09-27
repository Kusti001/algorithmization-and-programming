#define CRT_SECURE_NO_WARNINGS
#include <stdio.h>

int a; //главное число
int b; //основание
int p = 1; //начальная степень
int main(void) {
    printf("\nEnter a, b: ");
    int n = scanf("%d, %d",&a,&b);
    if (n != 2 || b < 2 || b > 32) {
        printf("Wrong Input");
        return 1;
    }

    // статья про перевод https://habr.com/ru/articles/852722/ (алгоритм 2)
    step1:
    if (p > a / b) {   // ищу максимальную степень b, меньше a  (это самое сложное здесь, но оно работает!!!)
        goto step2;
    }
    p*=b;
    goto step1;

    step2:
    printf("%d", a / p); //берём цифру из первого разряда
    a = a % p; //записываем остаток в а
    p /= b; //понижаем степень

    if (p > 0) {
        printf(",");
        goto step2;
    }
    return 0;
}