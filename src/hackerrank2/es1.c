#include <stdio.h>
#include <math.h>

int mcm(int a, int b) {
    int res = 1;

    while (res % a == 0) {// condizione 1

        if (res % b == 0) {// condizione 2
            return res; // res è divisibile per a e per b
        }
        res++;
    }

    printf("mcm between %d and %d is %d\n", a, b, res);

    return res;
}

void test_mcm(){
    mcm(2, 4);
    mcm(4, 2);
    mcm(3, 2);
    mcm(1, 2);
    mcm(60, 2);
    mcm(15, 15);
    mcm(15, 18);
    mcm(-15, 18);
    mcm(-15, -18);
    mcm(-2, -4);
    mcm(-2, 1);
    mcm(1, 1);
}

int main(void){
    test_mcm();
    return 0;
}

/*
int main(void) {
    int a, b;
    scanf("%d", &a);
    scanf("%d", &b);

    int mcm_res = mcm(a, b);

    printf("Il mcm tra %d e %d è: %d", a, b, mcm_res);
}
*/