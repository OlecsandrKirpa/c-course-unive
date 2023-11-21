#include <stdio.h>

unsigned int sum_array(unsigned int *x, unsigned int *fx, size_t size) {
    unsigned int sum = 0;

    for (size_t i = 0; i < size; i++) {
      sum = sum + x[i] + fx[i];
      printf("sum: %d\n", sum);
    }

    return sum;
}

int main(void) {
    unsigned int sum;
    unsigned int x[5] = {7, 9, 3};
    unsigned int fx[5];

    for (unsigned int i = 0; i < 5; i++) {
        fx[i] = x[i] + 1;
        printf("Setting fx[%d] to %d\n", i, fx[i]);
    }

    sum = sum_array(x, fx, 5);
    printf("%d", sum - 1);

    return 0;
}