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

char* readline();
char* ltrim(char*);
char* rtrim(char*);

int parse_int(char*);


int get_direction(const int *values, const int n_cols) {
  int direction = -2;
  int index = 0;
  while (direction == -2) {
    if (values[index] == values[index + 1]) {
      index++;
      continue;
    }

    bool is_row_even = index / n_cols % 2 == 0;
    if (is_row_even) {
      direction = values[index] > values[index + 1] ? -1 : 1;
    } else
      direction = values[index] > values[index + 1] ? 1 : -1;
  }

  return direction;
}

/*
 * Complete the 'snake' function below.
 *
 * The function is expected to return an INTEGER.
 * The function accepts following parameters:
 *  1. INTEGER POINTER values
 *  2. INTEGER n_rows
 *  3. INTEGER n_cols
 */

int snake(const int *values, const int n_rows, const int n_cols) {
  int direction = get_direction(values, n_cols);

  for (size_t i = 0; i < n_rows * n_cols; i++) {
    if (values[i] == values[i + 1])
      continue;

    bool is_row_even = i / n_cols % 2 == 0;
    bool next_row_is_even = (i + 1) / n_cols % 2 == 0;

        if (is_row_even && !next_row_is_even || !is_row_even &&
        next_row_is_even) {
          // Se la riga è pari e la successiva è dispari o viceversa, allora
          // l'elemento successivo è nella riga successiva.
          continue;
        }

    if (is_row_even) {
      if (direction == 1 && values[i] > values[i + 1])
        return 0;

      if (direction == -1 && values[i] < values[i + 1])
        return 0;

      continue;
    }

    if (direction == 1 && values[i] < values[i + 1])
      return 0;

    if (direction == -1 && values[i] > values[i + 1])
      return 0;
  }

  return direction;
}

int main()
{
    FILE* fptr = fopen(getenv("OUTPUT_PATH"), "w");


    int n_rows, n_cols;

    scanf("%d", &n_rows);
    scanf("%d", &n_cols);

    int *values = (int *)malloc(n_rows * n_cols * sizeof(int));

    for(unsigned int i = 0; i < n_rows * n_cols; i++){
        scanf("%d", values + i);
    }

    int result = snake(values, n_rows, n_cols);

    fprintf(fptr, "%d\n", result);

    fclose(fptr);

    return 0;
}

char* readline() {
    size_t alloc_length = 1024;
    size_t data_length = 0;

    char* data = malloc(alloc_length);

    while (true) {
        char* cursor = data + data_length;
        char* line = fgets(cursor, alloc_length - data_length, stdin);

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

char* ltrim(char* str) {
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

char* rtrim(char* str) {
    if (!str) {
        return '\0';
    }

    if (!*str) {
        return str;
    }

    char* end = str + strlen(str) - 1;

    while (end >= str && isspace(*end)) {
        end--;
    }

    *(end + 1) = '\0';

    return str;
}

int parse_int(char* str) {
    char* endptr;
    int value = strtol(str, &endptr, 10);

    if (endptr == str || *endptr != '\0') {
        exit(EXIT_FAILURE);
    }

    return value;
}
