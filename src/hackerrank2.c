//#include <stdio.h>
//#include <stdbool.h>
#include <math.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>
#include <limits.h>
#include <stdbool.h>

int mcm(int a, int b) {
    int res = 1;

    while (res % a == 0) {
        if (res % b == 0) return res;

        res++;
    }

    return res;
}

void exercise1() {
    printf("exercise1\n");
    printf("mcm(2, 4):   %d\n", mcm(2, 4));
    printf("mcm(-2, 4):  %d\n", mcm(-2, 4));
    printf("mcm(-2, -4): %d\n", mcm(-2, -4));
    printf("mcm(2, -4):  %d\n", mcm(2, -4));
    printf("mcm(4, 2):   %d\n", mcm(4, 2));
    printf("mcm(4, 4):   %d\n", mcm(4, 4));
    printf("mcm(3, 4):   %d\n", mcm(3, 4));
    printf("mcm(4, 3):   %d\n", mcm(4, 3));
    printf("mcm(10, 20): %d\n", mcm(10, 20));
}

void percentage() {
    printf("2 % 1 = %d\n", 2 % 1);
    printf("1 % 2 = %d\n", 1 % 2);
    printf("1%4 = %d\n", 1 % 4);
    printf("4%1 = %d\n", 4 % 1);
    printf("4%2 = %d\n", 4 % 2);
    printf("2%4 = %d\n", 2 % 4);
    printf("4%3 = %d\n", 4 % 3);
}


void oppermann(int limit) {
    unsigned i = 0;

    while (true) {
//        printf("while i=%d\n", i);
        unsigned a;
        for (unsigned j = 0; j < 10; j++) {
            a = i * 10 + j;
            if (a == limit) break; // primo break

            bool prime = true;
            for (unsigned k = 2; k < a; k++) {
                if (a % k == 0) {
                    prime = false;
                }

                break; // secondo break
            }

            if (prime && a != 0) printf("\t");
            else printf("%d\t", a);
        }

        printf("\n");

        if (a == limit) break; // terzo break
        i++;
    }
}

void breaks0() {
    while (true) {
        printf("while\n");
        break;
    }

    int j = 0;
    while (true) {
        printf("while; j=%d\n", j);
        for (unsigned i = 0; i < 10; i++) {
            printf("for; i=%d\n", i);
            if (i == 5) break;
        }

        if (j == 5) break;
        j++;
    }
}

/*
int a = 6;
int b = 9;
int c = 7;

int foo(int a, int b) {
    printf("foo: a=%d, b=%d\n", a, b);
    a = a;
    printf("a=a: a=%d, b=%d\n", a, b);

    if (b > 1 && (a % 2 == 0)) {
        printf("NEVER LOGGED\n");
        int b = 1;
        int a = 2 * b + 5;
        b += a;
    }

    return b - a + c;
}

int es3(void) {
    printf("es3\n");
    printf("a is %d\n", a);
    int a = 3;
    printf("a is %d\n", a);
    int r = foo(b, b * 2);
    c = 5;

    printf("%d\n", r);

    return 0;
}
*/

int func_name_as_var(int param) {
    int fuc_name_as_var = 3 + param;

    return fuc_name_as_var;
}

void swap(int *a, int b) {
    int c = *a;
    *a = b;
    b = c;
    return;
}

int es5(void) {
    int a = 5, b = 2;

    swap(&a, b);

    printf("a=%d b=%d\n", a, b);

    return 0;
}

void es6() {
    int d, k;
    scanf("%d", &d);
    scanf("%d", &k);

    int is_multiple = 1;

    for (int i = 0; i < k; i++) {
        int tmp;
        scanf("%d", &tmp);

        if (tmp % d != 0) {
            printf("false");
            return 0;
        }
    }

    printf("true");
}

//bool is_palindrome(int num) {
//    // Se il numero ha una singola cifra è palindromo.
//    if (num < 10) return true;
//
//    // Trasformiamo l'intero in stringa in modo da poter confrontare char per char
//    // usando gli indici.
//    char str[(int) (num / 10) + 2];
//    snprintf(str, sizeof(str), "%d", num);
//    int str_length = (int) strlen(str);
//
//    // Ci iteriamo la nostra bella stringa (array di char) e
//    // prendiamo l'elemento all'indice [0+i] e [<lunghezza_stringa> - 1 - i]
//    // in modo da confrontare i due char alla stessa distanza dall'inizio e dalla fine della stringa.
//    for (int i = 0; i < str_length; i++) {
//        int last_char_index = (str_length - 1) - i;
//
//        // Quando <lunghezza_stringa> - 1 - i == i
//        // Significa che siamo nella situazione in cui il nostro numero ha una quantità
//        // di cifre dispari, e che quindi
//        if (last_char_index == i) return true;
//
//        char first_char = str[i];
//        char last_char = str[last_char_index];
//
//        if (first_char != last_char) return false;
//    }
//
//    return true;
//}

/**
 * L'idea è la seguente:
 * Ci iteriamo i caratteri dall'inizio e dalla fine del nostro numero
 * e confrontiamo i caratteri con la stessa distanza dall'inizio e dalla fine.
 * Se i due caratteri alla stessa distanza non sono uguali, la cifra non è palindroma.
 */
bool is_palindrome(int num) {
    if (num < 0) return false;


//    printf("strlen for %d: %d | sizeof => %d; log10(num) => %d\n", num, (int)(num / 10) + 2, sizeof(num));
//    char str[(int) (num / 10) + 2];
    char str[1000];
    snprintf(str, sizeof(str), "%d", num);
    int str_length = (int) strlen(str);

    for (int i = 0; i < str_length; i++) {
        int last_char_index = (str_length - 1) - i;

        if (str[i] != str[last_char_index]) return false;
    }

    return true;
}

void es7() {
    int palindromes[34] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 11, 22, 33, 44, 55, 66, 77, 88, 99, 101, 111, 121, 131, 141,
                           151, 161, 171, 181, 191, 202, 2222, 3333, 1001, 900009};
    for (int i = 0; i < 34; i++)
        if (!(is_palindrome(palindromes[i]))) printf("Expected %d to be a palindrome number.\n", palindromes[i]);

    int not_palindromes[100] = {10, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32, 34,
                                35, 36, 37, 38, 39, 40, 41, 42, 43, 45, 46, 47, 48, 49, 50, 51, 52, 53, 54, 56, 57, 58,
                                59, 60, 61, 62, 63, 64, 65, 67, 68, 69, 70, 71, 72, 73, 74, 75, 76, 78, 79, 80, 81, 82,
                                83, 84, 85, 86, 87, 89, 90, 91, 92, 93, 94, 95, 96, 97, 98, 100, 102, 103, 104, 105,
                                106, 107, 108, 109, 110, 112, 113, 114, 115, 116, 117, 118, 119, 120};
    for (int i = 0; i < 100; i++)
        if (is_palindrome(not_palindromes[i]))
            printf("Expected %d NOT to be a palindrome number\n", not_palindromes[i]);

    printf("Es7 completed");

//    Find out not palindrome numbers with this function:
//    int palindromes_count = 0;
//    int current_palindrome_checking = 0;
//    printf("Ecco a te una lista di numeri non palindromi:\n{");
//    while(palindromes_count < 100){
//        if (!(is_palindrome(current_palindrome_checking))) {
//            printf("%d, ", current_palindrome_checking);
//            palindromes_count++;
//        }
//
//        current_palindrome_checking++;
//    }
//    printf("}");
}

//int es7() {
//    int arr[6] = {10, 12, 13, 101, 1, 22};
//    for (int i = 0; i < 6; i++) {
//        int tmp;
//        tmp = arr[i];
//
//        printf("is_palindrome(%d): %d\n\n", tmp, is_palindrome(tmp));
//    }
//
//    printf("true");
//
//    return 0;
//}

int char_to_int(const char ch) {
    return (int) ch - 48;
}

bool is_char_a_number(const char ch) {
    return ((int) ch >= 48) && ((int) ch <= 57);
}

/**
 * Transforms a string with numbers to array of numbers.
 * Separator between numbers can be literally anything.
 * @param str "10 20 30"
 * @param integers {10, 20, 30}
 * @return void
 */
void str_to_int_array(const char *str, int* integers) {
    const int str_length = strlen(str);
    int integer_index = 0;
    int last_was_integer = false;
    for (int i = 0; i < str_length + 1; i++) {
        const bool is_last_run = i == str_length;
        const char ch = is_last_run ? ' ' : str[i];
        const bool is_number = is_char_a_number(ch);
        // printf("index %d | ch: %c | is_number: %d | is_last_run: %d | ", i, ch, is_number, is_last_run);

        if (is_number) {
            int integer = char_to_int(ch);
            if (!last_was_integer) integers[integer_index] = integer;
            else {
                integers[integer_index] = integers[integer_index] * 10 + integer;
            }

            // printf("integer: %d | ", integer);
            // printf("integer_index: %d | ", integer_index);
            // printf("integers[integer_index]: %d", integers[integer_index]);
            last_was_integer = true;
        } else {
            if (last_was_integer) integer_index++;
            last_was_integer = false;
        }

        // printf("\n");
    }
}

void test_str_to_int_array() {
    int integers[3];
    str_to_int_array("10 20 30", integers);
    printf("integers: %d %d %d", integers[0], integers[1], integers[2]);
}

//    int k;
//    printf("k=? ");
//    scanf("%d\n", &k);

//    char *format_str = malloc(sizeof(char) * k * 3);

//    for(int i = 0; i < k * 3; i += 3) {
//        format_str[i] = '%';
//        format_str[i + 1] = 'd';
//
//        format_str[i + 2] = ' ';
//    }
//    format_str[(k * 3) - 1] = '\0';

//    printf("format_str is:\n%s\n", format_str);


// Main of es9
void es9() {
    int k;
    scanf("%d\n", &k);

    char *str = malloc(sizeof(char) * k * 5);
    scanf("%[^\n]%*c", str);

    int *numbers = malloc(sizeof(int) * k);
    str_to_int_array(str, numbers);

    int count = 0;
    for(int i = 0; i < k; i++) count += numbers[i] * 10;

    printf("%d\n", count);
}

int main(void) {
//    percentage();
//    exercise1();
//    oppermann(100);
//    breaks0();
//    es3();
//    printf("func_name_as_var(2) = %d\n", func_name_as_var(2));
//    es5();
//    es6();
//    es7();
//es9();
//    test_str_to_int_array();

    return 0;
}