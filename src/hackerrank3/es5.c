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

double media(int *v, size_t v_size) {
  double sum = 0;

  for (size_t i = 0; i < v_size; i++) {
    sum = sum + v[i];
  }

  return sum / v_size;
}

double deviazione_standard(int *v, size_t v_size) {
  double sum = 0;
  double m = media(v, v_size);

  for (size_t i = 0; i < v_size; i++) {
    sum = sum + pow(v[i] - m, 2);
  }

  return sqrt(sum / v_size);
}

/*
 * Complete the 'outlier_detection' function below.
 *
 * The function is expected to return an INTEGER.
 * The function accepts following parameters:
 *  1. INTEGER POINTER v
 *  2. SIZE_T v_size
 */
int outlier_detection(int *v, size_t v_size) {
  double limit = media(v, v_size) + 2 * deviazione_standard(v, v_size);
  printf("Media is %f\n", media(v, v_size));
  printf("Deviazione standard is %f\n", deviazione_standard(v, v_size));
  printf("number should be > %f\n", limit);
  printf("v_size: %lu\n", v_size);

  for (int i = 0; i < v_size; i++) {
    printf("v[%d]: %d\n", i, v[i]);
    if (v[i] > limit)
      return i;
  }

  return -1;
}

int main() {
  FILE *fptr = fopen(getenv("OUTPUT_PATH"), "w");

  size_t v_size = parse_int(ltrim(rtrim(readline())));

  int *v = malloc(v_size * sizeof(int));

  for (size_t i; i < v_size; i++) {
    v[i] = parse_int(ltrim(rtrim(readline())));
  }

  int result = outlier_detection(v, v_size);

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
