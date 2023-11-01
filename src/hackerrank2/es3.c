#include <stdio.h>

int a = 6;
int b = 9;
int c = 7;

int foo(int a, int b) {
    a = a;
    if (b > 1 && (a % 2 == 0)) {
        int b = 1;
        int a = 2 * b + 5;
        b += a;
    }

    return b - a + c;
}

int main(void) {
    int a = 3;
    int r = foo(b, b * 2);
    c = 5;

    printf("%d", r);

    return 0;
}