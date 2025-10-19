#include <stdio.h>

int A[10] = {5,3,6,7,8,5,3,6};
void foo(int arr[]) {
    printf("%p\n", arr);
}
int main(void) {
    printf("%p\n", A);
    for (int i = 0; i < 10; i++) {
        printf("%d ", A[i]);
    }
    printf("\n");
    for (int i = 0; i < 10; i++) {
        printf("%p  ", &A[i]);
    }
    printf("\n%d\n", sizeof(A));

    printf("%d\n", A[-4]);
    foo(A);
return 0;


}