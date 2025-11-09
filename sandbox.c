#include <stdio.h>

void cpuid(int code, unsigned int *a, unsigned int *b, unsigned int *c, unsigned int *d) {
    __asm__ volatile("cpuid"
                     : "=a"(*a), "=b"(*b), "=c"(*c), "=d"(*d)
                     : "a"(code));
}

int main() {
    unsigned int a, b, c, d;

    cpuid(0, &a, &b, &c, &d); // запрос 0: vendor string

    char vendor[13];
    ((unsigned int*)vendor)[0] = b;
    ((unsigned int*)vendor)[1] = d;
    ((unsigned int*)vendor)[2] = c;
    vendor[12] = '\0';

    printf("CPU vendor: %s\n", vendor);

    cpuid(1, &a, &b, &c, &d); // запрос 1: флаги и модель
    printf("Processor info: EAX=%08x, EBX=%08x, ECX=%08x, EDX=%08x\n", a, b, c, d);

    return 0;
}