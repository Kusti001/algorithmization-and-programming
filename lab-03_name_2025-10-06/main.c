#define CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void swap(int *pv) {
    int t = pv[0]; pv[0] = pv[1]; pv[1]=t;
}

int Ar[20];
/*
Быстрая сортировка:
Сложность: в среднем случае — O(n log n), В худшем - O(n^2) - когда опорным выбран МАКСИМАЛЬНЫЙ или МИНИМАЛЬНЫЙ элемент массива
+один из самых быстрых алгоритмов сортировки
-тяжело осознать из-за использования рекурсии
-глубина рекурсии (n log n) в среднем случае, (n - 1) - когда опорным выбран МАКСИМАЛЬНЫЙ или МИНИМАЛЬНЫЙ элемент в уже отсортированном массиве

Пузырьковая сортировка:
Сложность: в худшем случае — O(n²), В лучшем - O(n) - когда массив отсортирован изначально
+лёгкое понимание
+константная память

Сходства:
In-place (без создания доп массивов)
 */
void quick_sort(int ar[], int l, int r) {
    if (l < r) {
        int pivot = ar[r];
        int i = l - 1;
        for (int j = l; j < r; j++) {
            if (ar[j] < pivot) {
                i++;
                int tmp = ar[i];
                ar[i] = ar[j];
                ar[j] = tmp;
            }
        }
        int pivot_index = i + 1;
        int tmp = ar[pivot_index];
        ar[pivot_index] = ar[r];
        ar[r] = tmp;

        quick_sort(ar, l, pivot_index - 1);
        quick_sort(ar, pivot_index + 1, r);
    }
}

double find_median(int ar[], int n) {
    int m1 = 0, m2 = 0;

    for (int i = 0; i < n; i++) {
        int count = 0;
        for (int j = 0; j < n; j++) {
            if (ar[j] < ar[i])
                count++;
        }

        if (n % 2 == 1 && count == n / 2)
            return ar[i];

        if (n % 2 == 0) {
            if (count == n / 2 - 1) m1 = ar[i];
            if (count == n / 2) m2 = ar[i];
        }
    }
    return (m1 + m2) / 2.0;
}

int main(void) {
    time_t curtime;
    time(&curtime);
    srand((unsigned int) curtime);

    int n = sizeof(Ar) / sizeof(Ar[0]);
    for (int i = 0; i < n; i++) {
        Ar[i] = rand() % 1000;
    }


    for (int i = 0; i < n; i++){
        printf("%d\n", Ar[i]);
    }

    /*for (int i = 0; i < n; i++) {
        for (int j = 0; j < (n -1); j++) {
            if (Ar[j] < Ar[j + 1]) {
                swap(&Ar[j]);
                flag = 1;
            }
        }
        if (flag == 0) break;
    } */

    quick_sort(Ar, 0, n - 1);

    printf("\n");
    char ch = ',';
    for (int i = 0; i < n; i++) {
        if (i == n-1) ch = ' ';
        printf("%05d%c", Ar[i],ch);
    }

    double med = find_median(Ar, n);
    printf("\nМедиана: %.2f\n", med);

    return 0;
}


//1. заменить алгоритм сортировки +
//2. найти медиану      *без сортировки
//3. размер массива любой + генератор случайных чисел впихнуть +