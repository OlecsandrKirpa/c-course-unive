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
char *ltrim(char *);
char *rtrim(char *);

int parse_int(char *);

// Method "swap" and "sort_desc" were taken (but modified) from
// https://www.geeksforgeeks.org/c-program-to-sort-an-array-in-ascending-order/
void swap(int *a, int *b) {
  int temp = *a;
  *a = *b;
  *b = temp;
}

void sort_desc(int *arr, int n) {
  int i, j, max_index;

  for (i = 0; i < n - 1; i++) {
    max_index = i;

    for (j = i + 1; j < n; j++) {
      if (arr[j] > arr[max_index]) {
        max_index = j;
      }
    }

    if (max_index != i) {
      swap(&arr[i], &arr[max_index]);
    }
  }
}

/**
 *
 * Given an array ordered desc:
 *
 * This method tries to reduce the budget of the user.
 * It tries to take the first $target elements and sum them.
 * If that sum is less than the budget, it will be the new budget.
 * This because we cannot spend more than that.
 * Otherwise, if by taking the first $target element we go higher than the
 * original budget, just return the original budget.
 *
 * This is REALLY useful because if we know already what the maximum amount of
 * money spent is, we can reduce significantly the amount of recursive calls.
 *
 */
int minify_budget(const int *prizes, const int prizes_size, const int budget,
                  const int target) {
  int spent = 0;
  int missing = target;

  int index = 0;
  while (missing > 0 && index < prizes_size) {
    if (spent + prizes[index] > budget)
      return budget;

    spent += prizes[index];
    missing--;
    index++;
  }

  return spent;
}

int calls = 0;
int gift_rec(int *prizes, const int prizes_size, const int budget,
             const int target, const int spent) {
  calls++;

  //    printf("gift_rec | budget: %d | target: %d | spent: %d | prizes: ",
  //    budget, target, spent); for (int i = 0; i < prizes_size; ++i) {
  //      printf("%d ", prizes[i]);
  //    }
  //    printf("\n");

  if (target == 0) {
    //    printf("Target is zero. Returning spent %d\n", spent);
    return spent;
  }

  if (budget < 0) {
    printf("Budget < 0 should never happen :(\n");
    exit(EXIT_FAILURE);
  }

  if (target < 0) {
    printf("Target < 0 should never happen :(\n");
    exit(EXIT_FAILURE);
  }

  int max = 0;
  for (int i = 0; i < prizes_size; ++i) {
    const int prize = prizes[i];
    // Current gift is too expensive
    if (prize > budget)
      continue;

    if (prize == 0)
      continue;

    // If current prize is exactly the budget, and we need just one more gift,
    // buy this gift and return.
    // If we need more tha one gift, then skip to next scenario: we're going to
    // use all the remaining money and won't be able to purchase other gifts.
    if (prize == budget) {
      if (target > 1)
        continue;

      return spent + prize;
    }

    prizes[i] = 0;
    const int current = gift_rec(prizes, prizes_size, budget - prize,
                                 target - 1, spent + prize);
    prizes[i] = prize;

    // TODO check what happens when current is budget but int that scenario we
    // did not buy $target quantity of gifts.
    if (current == budget)
      return current;

    if (current > max)
      max = current;
  }

  return max;
}

int gift(int prizes_size, int *prizes, int budget, int target_prizes) {
  sort_desc(prizes, prizes_size);

  calls = 0;

  const int result =
      gift_rec(prizes, prizes_size,
               minify_budget(prizes, prizes_size, budget, target_prizes),
               target_prizes, 0);
  //    printf("Done in %d calls\n", calls);
  return result;
}

void test_case(int *prizes, int prizes_size, int budget, int target_prizes,
               int call_row, int expected) {
  const int actual = gift(prizes_size, prizes, budget, target_prizes);
  if (actual == expected)
    return;

  printf("[FAIL:%d] Expected %d but got %d\n", call_row, expected, actual);
}

int test() {
  test_case((int[]){1, 2, 3, 7, 8, 10}, 6, 20, 3, __LINE__, 20);

  test_case((int[]){10, 8, 3, 7, 8, 10}, 6, 34, 4, __LINE__, 33);

  test_case((int[]){10, 8, 3, 7, 8, 10, 33, 33, 33}, 9, 100, 3, __LINE__, 99);
  test_case((int[]){10, 8, 3, 7, 33, 8, 10, 33, 33}, 9, 100, 3, __LINE__, 99);
  test_case((int[]){10, 8, 7, 33, 8, 10, 33, 3, 33}, 9, 100, 3, __LINE__, 99);
  test_case((int[]){10, 8, 3, 7, 8, 10, 33, 33, 34}, 9, 100, 3, __LINE__, 100);
  test_case((int[]){10, 8, 3, 7, 8, 10, 33, 34, 34}, 9, 100, 3, __LINE__,
            34 + 34 + 10);
  test_case((int[]){10, 8, 3, 7, 8, 10, 50, 34, 34}, 9, 100, 3, __LINE__,
            50 + 34 + 10);
  test_case((int[]){10, 34, 8, 3, 7, 8, 50, 10, 34}, 9, 100, 3, __LINE__,
            50 + 34 + 10);
  test_case((int[]){10, 34, 8, 3, 7, 8, 50, 10, 34, 40, 40, 40, 40, 40, 40, 40},
            16, 100, 3, __LINE__, 50 + 40 + 10);

  test_case((int[]){9,  13, 14, 8,  11, 6,  11, 5, 5, 0,  8,  3, 11, 2,
                    10, 2,  8,  3,  8,  10, 7,  2, 0, 6,  10, 2, 12, 12,
                    13, 7,  13, 13, 7,  2,  0,  5, 1, 11, 1,  12},
            40, 78, 6, __LINE__, 78);

  test_case((int[]){9,  13, 14, 8,  11, 6,  11, 5, 5, 0,  8,  3, 11, 2,
                    10, 2,  8,  3,  8,  10, 7,  2, 0, 6,  10, 2, 12, 12,
                    13, 7,  13, 13, 7,  2,  0,  5, 1, 11, 1,  12},
            40, 76, 6, __LINE__, 76);

  test_case((int[]){9,  13, 14, 8,  11, 6,  11, 5, 5, 0,  8,  3, 11, 2,
                    10, 2,  8,  3,  8,  10, 7,  2, 0, 6,  10, 2, 12, 12,
                    13, 7,  13, 13, 7,  2,  0,  5, 1, 11, 1,  12},
            40, 100, 6, __LINE__, 78);
  return 0;
}

int main() {
  //    return test();

  FILE *fptr = fopen(getenv("OUTPUT_PATH"), "w");

  int b = parse_int(ltrim(rtrim(readline())));

  int n = parse_int(ltrim(rtrim(readline())));

  int v_count = parse_int(ltrim(rtrim(readline())));

  int *v = malloc(v_count * sizeof(int));

  for (int i = 0; i < v_count; i++) {
    int v_item = parse_int(ltrim(rtrim(readline())));

    *(v + i) = v_item;
  }

  int result = gift(v_count, v, b, n);

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

char *ltrim(char *str) {
  if (!str) {
    return '\0';
  }

  if (!*str) {
    return str;
  }

  while (*str != '\0' && isspace(*str)) {
    str++;
  }

  return str;
}

char *rtrim(char *str) {
  if (!str) {
    return '\0';
  }

  if (!*str) {
    return str;
  }

  char *end = str + strlen(str) - 1;

  while (end >= str && isspace(*end)) {
    end--;
  }

  *(end + 1) = '\0';

  return str;
}

int parse_int(char *str) {
  char *endptr;
  int value = strtol(str, &endptr, 10);

  if (endptr == str || *endptr != '\0') {
    exit(EXIT_FAILURE);
  }

  return value;
}
