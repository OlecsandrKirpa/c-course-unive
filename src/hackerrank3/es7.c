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

char **split_string(const char *arr, const size_t arr_size,
                    const char delimiter, int *result_size) {

  *result_size = 1;
  for (int i = 0; i < arr_size; i++) {
    if (arr[i] == delimiter) {
      (*result_size)++;
    }
  }

  char **result = malloc((*result_size) * sizeof(char *));
  //  char **result = malloc((*result_size) * arr_size);
  for (int i = 0; i < (*result_size); i++) {
    result[i] = malloc(arr_size * sizeof(char));
  }

  int result_index = 0;
  int char_index = 0;
  for (size_t i = 0; i < arr_size; i++) {
    if (arr[i] == delimiter) {
      result[result_index][char_index] = '\0';
      // TODO resize array to only the needed space.
      result_index++;
      char_index = 0;
      continue;
    }

    result[result_index][char_index] = arr[i];
    char_index++;
  }

  return result;
}

/*
void test_split_string(void) {
  char *arr = "123|321|456|654";
  size_t arr_size = strlen(arr);
  int result_size = 0;
  char **result = split_string(arr, arr_size, '|', &result_size);

  printf("Orig: %s\n", arr);
  for (int i = 0; i < result_size; i++) {
    printf("result[%d]: %s\n", i, result[i]);
  }
  printf("\n");

  //
-----------------------------------------------------------------------------

  arr = "1323XX1120X|3XXXX100XX3X|1XX000X|303020X1X212";
  arr_size = strlen(arr);
  result_size = 0;
  result = split_string(arr, arr_size, '|', &result_size);

  printf("Orig: %s\n", arr);
  for (int i = 0; i < result_size; i++) {
    printf("result[%d]: %s\n", i, result[i]);
  }
  printf("\n");

  //
-----------------------------------------------------------------------------

  arr = "XX2123123123145|5X2X2X2X2X2X2|";
  arr_size = strlen(arr);
  result_size = 0;
  result = split_string(arr, arr_size, '|', &result_size);

  printf("Orig: %s\n", arr);
  for (int i = 0; i < result_size; i++) {
    printf("result[%d]: %s\n", i, result[i]);
  }
  printf("\n");
}
 */

int count_max_number_of_consecutive_X(char *str) {
  int max = 0;
  int current = 0;

  for (size_t i = 0; i < strlen(str); i++) {
    if (str[i] == 'X') {
      current++;
      continue;
    }

    if (current > max)
      max = current;

    current = 0;
  }

  if (current > max)
    max = current;

  return max;
}

/*
void test_count_max_number_of_consecutive_X(void) {
  char *str;
  int max;

  max = count_max_number_of_consecutive_X(str = "XX212XXX");
  printf("str: %s | max: %d\n", str, max);

  // -------------------------------------------------

  max = count_max_number_of_consecutive_X(str = "132X2X2X2X2");
  printf("str: %s | max: %d\n", str, max);
}*/

/*
 * Complete the 'sabermetrica' function below.
 *
 * The function is expected to return an INTEGER.
 * The function accepts following parameters:
 *  1. CHAR POINTER v
 *  2. SIZE_T v_size
 *  3. INTEGER POINTER n
 */

int sabermetrica(char *v, size_t v_size, int *best_player_index) {
  // Dentro points salverò i punti di ogni giocatore
  int *points = malloc(v_size * sizeof(int));
  int players_count = 0;
  char **players = split_string(v, v_size, '|', &players_count);

  for (size_t i = 0; i < players_count; i++) {
    points[i] = count_max_number_of_consecutive_X(players[i]);
  }

  int max = 0;
  for (int i = 0; i < players_count; i++) {
    if (points[i] > max) {
      max = points[i];
      *best_player_index = i;
    }
  }

  return max;
}

int main() {
  FILE *fptr = fopen(getenv("OUTPUT_PATH"), "w");

  int v_size = parse_int(ltrim(rtrim(readline())));

  char *v = malloc(v_size * sizeof(char));

  for (size_t i; i < v_size; i++) {
    char aux;
    scanf("%c", &aux);
    v[i] = aux;
  }

  int n;

  int result = sabermetrica(v, v_size, &n);

  fprintf(fptr, "%d\n%d", n, result);

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
