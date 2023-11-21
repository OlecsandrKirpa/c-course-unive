#include <stdio.h>

void diminuendo(int *v) {
    while (*v <= *(v + 1)) {
        (*v)++;
    }
}

void print_array(int v[], size_t size) {
    for (size_t i = 0; i < size; ++i) {
        printf("%d ", v[i]);
    }
    printf("\n");
}

int main(void) {
    int v[10] = {0, 1, 2, 0, 4, 5, 0, 7, 8, 0};

    // loop 2
    for (int i = v_size - 1; i >= 0; --i) {
        if (*(v + i) >= *(v + i - 1)) {
            diminuendo(v + i - 1);
        }
    }
    print_array(v, 10);
}