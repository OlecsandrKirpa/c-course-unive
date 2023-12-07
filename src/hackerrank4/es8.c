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


/*
 * Complete the 'char_dist' function below.
 *
 * The function is expected to return an INTEGER.
 * The function accepts following parameters:
 *  1. CHARACTER_ARRAY s1
 *  2. CHARACTER_ARRAY s2
 *  3. INTEGER d
 */

int char_dist(char *s1, char *s2, int d) {
  if (strlen(s1) == 0) return 1;

  int i_dist = s1[0] - s2[0];
  if (i_dist < 0) i_dist = s2[0] - s1[0];
  return i_dist == d ? char_dist(s1 + 1, s2 + 1, d) : 0;

  // Versione non ricorsiva:
  //  for (int i = 0; i < strlen(s1); i++) {
  //    int i_dist = s1[i] - s2[i];
  //    if (i_dist < 0) i_dist =  s2[i] - s1[i];
  //
  //    if (i_dist != d) return false;
  //  }
  //
  //  return true;
}
int main()
{
    FILE* fptr = fopen(getenv("OUTPUT_PATH"), "w");

    int s1_count = parse_int(ltrim(rtrim(readline())));

    char* s1 = malloc((s1_count)+1 * sizeof(char));

    for (int i = 0; i < s1_count; i++) {
        char* s1_item = *readline();

        *(s1 + i) = s1_item;
    }
    *(s1 + s1_count) = '\0';

    int s2_count = parse_int(ltrim(rtrim(readline())));

    char* s2 = malloc((s2_count+1) * sizeof(char));

    for (int i = 0; i < s2_count; i++) {
        char* s2_item = *readline();

        *(s2 + i) = s2_item;
    }
    *(s2 + s2_count) = '\0';

    int d = parse_int(ltrim(rtrim(readline())));

    int result = char_dist(s1, s2, d);

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
