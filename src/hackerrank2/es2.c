#include <stdbool.h>
#include <stdio.h>

int main(void) {
    int limit;
    unsigned i = 0;

    scanf("%d", &limit);

    while (true) {
        unsigned a;
        for (unsigned j = 0; j < 10; j++) {
            a = i * 10 + j;
            if (a == limit) {
                break; // primo break
            }
            bool prime = true;
            for (unsigned k = 2; k < a; k++) {
                if (a % k == 0) {
                    prime = false;
                    break; // secondo break
                }
            }
            if (prime && a != 0) {
                printf("\t");
            } else {
                printf("%d\t", a);
            }
        }
        printf("\n");
        if (a == limit) {
            break; // terzo break
        }
        i++;
    }
    return 0;
}