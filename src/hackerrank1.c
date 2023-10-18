#include <stdio.h>
#include <stdbool.h>

void exercise1() {
    int a;
    double b = 3.14159;
    unsigned int c;

    a = b * a;
    c = c + (b = a) - 100;

    printf("a = %d\n", a);
    printf("b = %f\n", b);
    printf("c = %u\n", c);
}

void exercise3() {
    int a = 1;
    int b = 0;
    int c = 5;

    int res;

    // res = 0
    res = b && b + (a = c); // Prima espressione

    printf("a riga 27: %d\n", a);

    // a = 13
    a = a + (a - c) + -(a + c) - 4; // Seconda espressione

    printf("a riga 32: %d\n", a);

    // b = 5
    b = a * b * 100 + c;

    printf("res: %d\n", res);
    printf("a: %d\n", a);
    printf("b: %d\n", b);
    printf("c: %d\n", c);
}

int num2() {
    printf("num2()");
    return 2;
}

int num0() {
    printf("num0()");
    return 0;
}

int num1() {
    printf("num1()");
    return 1;
}

void andInMathOperations() {
    printf("1 && 15 + 9 equals: %d\n", 1 && 15 + 9);
    printf("1 && 15 + 9 equals: %d\n", 15 || 9);

    printf("order 0:");
    int order = num1() && num1() * num2();
    printf("\norder 1:");
    num2() * num0() || num1();
    printf("\norder 2:");
    num2() && num0() || num1();
    printf("\norder 3:");
    num2() || num0() && num1();
}

void taxes(double gross_income) {
    double threshold_1 = 15000.0;
    double threshold_2 = 28000.0;
    double threshold_3 = 50000.0;

    printf("gross_income: %f ", gross_income);

    double taxes = 0;
    if (gross_income > threshold_3) {
        taxes += (gross_income - threshold_3) * 0.43;
        gross_income -= gross_income - threshold_3;
    }
    if (gross_income > threshold_2) {
        taxes += (gross_income - threshold_2) * 0.35;
        gross_income -= gross_income - threshold_2;
    }
    if (gross_income > threshold_1) {
        taxes += (gross_income - threshold_1) * 0.25;
        gross_income -= gross_income - threshold_1;
    }
    if (gross_income > 0) {
        taxes += gross_income * 0.23;
    }

    printf("gross_income: %f; taxes: %f\n", gross_income, taxes);
}

void ifElseExample() {
    int trueOrFalse = false;
    if (trueOrFalse) {
        printf("Inside first if");
    } else {
        printf("Inside first else\n");
    }

    if (!trueOrFalse) {
        printf("Inside second if\n");
    }

    int anni = 20;
    if (anni < 18) printf("Poppante");
    if (anni > 18 && anni < 40) printf("Ragazzo");
    if (anni >= 40) printf("Dinosauro");
}

void es6(int a) {
    printf("es6: a = %d; ", a);

    if (a < 10) printf("a");

    if (a < 30) printf("b");
    else if (a > 50) printf("c");

    if (a == 40) printf("d");
    else if (a > 60) printf("e");
    else if (a > 100) printf("f");

    if (a == 29) printf("g");
    else printf("h");

    printf("\n");
}

int es7(unsigned int a, unsigned int b) {
    return a <= b ? (b > a ? 1 : 2) : (b + a < 1 ? 3 : 4);
}

int es8_max3(int a, int b, int c) {
    return (a > b) ? ((a > c) ? a : c) : ((b > c) ? b : c);
}

int es9(int a, int b, int c) {
    int x = (a < b) * (a <= c) * a;
    int y = (c > b) * (c >= a) * c;

    printf("a=%d; b=%d; c=%d; x*y=%d\n", a, b, c, x * y);

    return 0;
}

int main(void) {
//    printf("0 && 0 + 2: %d\n", 0 && 0 + 2);
//    printf("1 && 2 + 2: %d\n", 1 && 2 + 2);
//    printf("5 && 2 + 2: %d\n", 5 && (2 + 2)); // 2 + 2 != 0
//    exercise1();
//    exercise3();
//    andInMathOperations();
//    taxes(10000);
//    taxes(15000);
//    taxes(15001);
//    taxes(20000);
//    taxes(30000);
//    taxes(60000);
//    ifElseExample();
//    es6(5);
//    es6(10);
//    es6(15);
//    es6(30);
//    es6(50);
//    es6(40);
//    es6(29);
//    es6(59);

//    for (int a = 0; a < 10000; a++) {
//        for (int b = 0; b < 10000; b++) {
//            int result = es7(a, b);
//            if (result == 3) printf("il risultato è 3 per a = %d e b = %d", a, b);
//        }
//    }

//    printf("max tra 1,2,3: %d\n", es8_max3(1, 2,3));
//    printf("max tra 1,2,3: %d\n", es8_max3(3, 2,1));
//    printf("max tra 1,2,3: %d\n", es8_max3(2, 3,1));
//    printf("max tra 1,2,3: %d\n", es8_max3(2, 1,3));

//    printf("1 < 2 = %d\n", 1 < 2);
//    printf("2 < 1 = %d\n", 2 < 1);

    return 0;
}