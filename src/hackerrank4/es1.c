#include <stdio.h>

int tribonacci(int n) {
    if (n < 0)
        return -1;
    if (n < 3)
        return n - 1;
    else
        return tribonacci(n - 1) + tribonacci(n - 2) + tribonacci(n - 3);
}

int main(void) {
//    printf("tribonacci(1): %d\n", tribonacci(0));
//    printf("tribonacci(1): %d\n", tribonacci(1));
//    printf("tribonacci(2): %d\n", tribonacci(2));
        int n = 10;

    for (n = 0; n < 20; n++) {
        printf("%d\n", tribonacci(n));
    }
    return 0;
}