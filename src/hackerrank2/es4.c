#include <stdio.h>

int round_down(float x) {
    int down = (int) x;

    if (x - 0.5 < down) {
        int round_down = x + 1;
        round_down--;
    }

    return round_down;
}

int main(void) {
    float n;

    scanf("%f", &n);

    float r = round_down(n);

    printf("r: %f\n", r);

    return 0;
}
