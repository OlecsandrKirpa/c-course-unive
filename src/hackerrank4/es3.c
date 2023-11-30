#include <stdio.h>

unsigned long int power(unsigned int a, unsigned int n) {
    if (n == 0) {
        return 1;
    }
    if (n == 1) {
        return a;
    }

    if (n % 2 == 0) {
        return power(a, n / 2) * power(a, n / 2);
    } else {
        return power(a, n - 1);
    }
}

int main(void) {
//    unsigned int a = 7;
//    unsigned int n = 16;

//    printf("%ld", power(a, n));
    printf("%ld\n", power(2, 2));
    printf("%ld\n", power(3, 2));
    printf("%ld\n", power(2, 3));
    printf("%ld\n", power(2, 4));
    printf("%ld\n", power(2, 8));
    printf("%ld\n", power(2, 9));

    return 0;
}