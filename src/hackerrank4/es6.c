#include <assert.h>
#include <ctype.h>
#include <limits.h>
#include <math.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *readline();

/*
 * Complete the 'monkey' function below.
 *
 * The function is expected to return an SIZE_T.
 * The function accepts following parameters:
 *  1. STRING string
 *  2. STRING pattern
 */

size_t monkey(const char *string, const char *pattern) {
  // Caso base implicito:
  // se string è vuota, strlen(string) == 0.
  // se strlen(string) == 0 il codice non entra nel loop for ma ritorna
  // direttamente 0.

  for (int i = 0; i < strlen(string); i++) {
    int k = 0;
    while (string[i + k] == pattern[k]) {
      if (k == strlen(pattern) - 1)
        return 1 + monkey(string + i + 1, pattern); // Con ripetizioni
        //return 1 + monkey(string + i + k + 1, pattern); // Senza ripetizioni

      k++;
    }
  }

  return 0;
}

void test_monkey_example(const char *str, const char *pattern,
                         const int expected) {
  int actual = monkey(str, pattern);
  if (actual == expected)
    return;

  printf("[TEST FAILED] str: %s | pattern: %s | expected was %d | got %d\n", str,
         pattern, expected, actual);
}

int main() {
  test_monkey_example("casdasdiciao-ciao123ci1ao", "ciao", 2);

  test_monkey_example(
      "asdfiasndflasdnfalksdjfbanpwinsdldadfasdfaskdjfasoidfcbaoieufrtewahflnvs"
      "oisjlandskjfasdifcabsodifuaisdfhausodfhaosndfuhasdfgas",
      "sdfasdfiu", 0); // Test case 3
      test_monkey_example("gigigigigigigigigigigigigiggigigigigiigigigigigi",
      "gigi", 20); // Test case 2
  test_monkey_example("sqdsassiczkdvpewlsassizdmcbpsdsassidfd", "sassi", 3);
  // test 0
  test_monkey_example("dfaricaricaricaadfanskdfaricasasda", "ricarica",
                      2);                                        // test 1
  test_monkey_example("aaaaaaaaaaaaaaaaaaaaaaaaaaaaa", "a", 29); // test 4
  return 0;

  FILE *fptr = fopen(getenv("OUTPUT_PATH"), "w");

  char *string = readline();

  char *pattern = readline();

  int result = monkey(string, pattern);

  fprintf(fptr, "%d\n", result);

  fclose(fptr);

  return 0;
}

char *readline() {
  size_t alloc_length = 1024;
  size_t data_length = 0;

  char *data = malloc(alloc_length);

  while (true) {
    char *cursor = data + data_length;
    char *line = fgets(cursor, alloc_length - data_length, stdin);

    if (!line) {
      break;
    }

    data_length += strlen(cursor);

    if (data_length < alloc_length - 1 || data[data_length - 1] == '\n') {
      break;
    }

    alloc_length <<= 1;

    data = realloc(data, alloc_length);

    if (!data) {
      data = '\0';

      break;
    }
  }

  if (data[data_length - 1] == '\n') {
    data[data_length - 1] = '\0';

    data = realloc(data, data_length);

    if (!data) {
      data = '\0';
    }
  } else {
    data = realloc(data, data_length + 1);

    if (!data) {
      data = '\0';
    } else {
      data[data_length] = '\0';
    }
  }

  return data;
}
