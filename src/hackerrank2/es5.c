#include<stdio.h>

void swap(int *a, int b) {
    int c = *a;
    *a = b;
    b = c;
    return;
}

int main(void) {
    int a = 5, b = 2;

    swap(&a, b);

    printf("a=%d b=%d\n", a, b);

    return 0;
}