#include <math.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>
#include <limits.h>
#include <stdbool.h>

// Using ascii table, we can convert a char to a int by:
// 1. Casting the char into an int => now we have the ascii index of the char
// 2. Subtracting the index of the char '0'.
// param is marked as 'const' because it's a good practice to mark as readonly anything you don't need to update.
int char_to_int(const char ch) {
    return (int) ch - 48;
}

bool is_char_a_number(const char ch) {
    return ((int) ch >= 48) && ((int) ch <= 57);
}

/**
 * Transforms a string with numbers to array of numbers.
 * Separator between numbers can be literally anything than a number.
 * @param str "10 20 30"
 * @param integers {10, 20, 30}
 * @return void
 *
 * How it works:
 * It iterates @param str and when it finds a number char,
 * it writes the value of the char converted into a integer inside the @param integers
 * at the `integer_index` value. When it finds multiple chars that are numbers consecutively,
 * it multiplies the value of the current value of that index of our array of numbers `integers` by 10 and
 * then it adds the value of the current char converted in integer.
 * Then, when it fids a non-number char, it increases the value of `integer_index`.
 */
void str_to_int_array(const char *str, int* integers) {
    const int str_length = (int)strlen(str);
    int integer_index = 0;
    int last_was_integer = false;
    for (int i = 0; i < str_length + 1; i++) {
        const bool is_last_run = i == str_length;
        const char ch = is_last_run ? ' ' : str[i];
        const bool is_number = is_char_a_number(ch);

        if (is_number) {
            int integer = char_to_int(ch);
            if (last_was_integer) integers[integer_index] = integers[integer_index] * 10 + integer;
            else integers[integer_index] = integer;

            last_was_integer = true;
        } else {
            if (last_was_integer) integer_index++;
            last_was_integer = false;
        }
    }
}


int main() {
    int k;
    scanf("%d\n", &k);

    char *str = malloc(sizeof(char) * k * 5);
    scanf("%[^\n]%*c", str);

    int *numbers = malloc(sizeof(int) * k);
    str_to_int_array(str, numbers);

    // Accumulator
    int acc = 0;
    for(int i = 0; i < k; i++) acc += numbers[i] * 10;

    printf("%d\n", acc);

    // Don't forget to free :)
    free(str);
    free(numbers);

    return 0;
}