#define CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int a, b,c,d;
int *p1 = &a, *p2 = &b, *p3 = &c, *p4 = &d;
typedef long long int ll;

void init_rng(void) {
    time_t curtime;
    time(&curtime);
    printf("Current Time: %ld\n", curtime);
    srand((unsigned int) curtime);
    rand();rand();rand();

}
int gen_rnd_int(void) {
    const ll t = ((ll) rand() * 1000)/RAND_MAX;
    return (int) t;

}
void swap(int **x, int **y) {
    int *tmp = *x;  // сохраняем адрес, на который указывает первый указатель
    *x = *y;        // первый указатель теперь указывает туда же, куда указывал второй
    *y = tmp;
}

int main(void) {
    init_rng();
    a = gen_rnd_int(); b = gen_rnd_int(); c = gen_rnd_int(); d = gen_rnd_int();

    if (*p1 > *p2) swap(&p1, &p2);
    if (*p2 > *p3) swap(&p2, &p3);
    if (*p3 > *p4) swap(&p3, &p4);
    if (*p1 > *p2) swap(&p1, &p2);
    if (*p2 > *p3) swap(&p2, &p3);
    if (*p1 > *p2) swap(&p1, &p2);
    printf("Переменные:\n%d %d %d %d\n", a,b,c,d);
    printf("Указатели:\n%d %d %d %d", *p1, *p2, *p3, *p4);


    return 0;
}


/* четыре переменные, нужно отсортировать, меняя указатели местами. сами переменные не меняем
 *
 *
 *
 */