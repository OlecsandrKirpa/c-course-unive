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

struct position {
    size_t pos;
    struct position *next;
};

struct occ {
    int elem;
    struct position *positions;
    struct occ *next;
};

struct list {
  int data;
  struct list *next;
};


typedef struct position position_t;
typedef struct occ occ_t;
typedef struct list list_t;

void free_positions(position_t *pos) {
    if (pos == NULL)
        return;
    free_positions(pos->next);
    free(pos);
}

void free_occ(occ_t *occ) {
    if (occ == NULL)
        return;
    free_positions(occ->positions);
    free_occ(occ->next);
    free(occ);
}
void print_occ(occ_t *res, FILE* fptr) {
    while (res != NULL) {
        fprintf(fptr, "%d: ", res->elem);
        position_t *pos = res->positions;
        fprintf(fptr, "[");
        while (pos != NULL) {
            fprintf(fptr, " %zu", pos->pos);
            pos = pos->next;
        }
        fprintf(fptr, " ]");
        fprintf(fptr, "\n");
        res = res->next;
    }
}

void append(list_t *l, int elem) {
    list_t *new_elem = malloc(sizeof(list_t));
    new_elem->data = elem;
    new_elem->next = 0;

    l->next = new_elem;
}

/*
 * Complete the 'count_occ' function below.
 *
 * The function is expected to return a pointer to occ*.
 * The function accepts list_t *l as parameter.
 */

// current cannot be nil. Check current before call.
// returns reference to occ_t if found, NULL otherwise.
occ_t *find_occ(int value, occ_t *current) {
  while (current && current->next && current->next->elem <= value) {
    current = current->next;
  }

  return current && current->elem == value ? current : NULL;
}

void add_occ_if_missing(int value, occ_t **original) {
  occ_t *current = *original;
  while (current && current->next && current->next->elem <= value) {
    current = current->next;
  }

  if (current == NULL) {
    printf("Hai sbagliato qualcosa. current non dovrebbe poter avere valore "
           "NULL.");
    exit(EXIT_FAILURE);
  }

  if (current->elem == value)
    return;

  // A questo punto, dobbiamo far puntare current->next al nuovo elemento.
  occ_t *new = malloc(sizeof(occ_t));
  new->next = current->next;
  current->next = new;
  new->elem = value;
}

occ_t *find_or_add_occ(int value, occ_t **original) {
  add_occ_if_missing(value, original);
  return find_occ(value, *original);
}

void add_position_to_occ(int index, occ_t **original) {
  // Caso base: positions è vuoto.
  if ((*original)->positions == NULL) {
    (*original)->positions = malloc(sizeof(position_t));
    (*original)->positions->pos = index;
    (*original)->positions->next = NULL; // just in case
    return;
  }

  position_t *last_position = (*original)->positions;
  while (last_position && last_position->next) {
    last_position = last_position->next;
  }

  if (last_position == NULL) {
    printf("Hai sbagliato qualcosa. last_position non dovrebbe poter avere "
           "valore NULL.");
    exit(EXIT_FAILURE);
  }

  last_position->next = malloc(sizeof(position_t));
  last_position->next->pos = index;
  last_position->next->next = NULL; // just in case
}

occ_t *count_occ(list_t *l) {
  if (!l)
    return NULL;

  occ_t *result = malloc(sizeof(occ_t));
  result->next = NULL;
  result->positions = NULL;
  result->elem = 0;

  int index = 0;
  while (l) {
    occ_t *original = find_or_add_occ(l->data, &result);
    add_position_to_occ(index, &original);

    l = l->next;
    index++;
  }

  result = result->positions == NULL ? result->next : result;

  return result;
}

int main()
{
    FILE* fptr = fopen(getenv("OUTPUT_PATH"), "w");

    int n;
    scanf("%d", &n);
    list_t *l1;
    if(n > 0){
        l1 = malloc(sizeof(list_t));
    } else{
        l1 = NULL;
    }

    list_t *cursor_l1 = l1;

    for (int i = 0; i < n; ++i) {
        int value_to_add;
        scanf("%d", &value_to_add);
        if(i==0){
            l1->data = value_to_add;
            continue;
        }
        append(cursor_l1, value_to_add);
        cursor_l1 = cursor_l1->next;
    }

    occ_t *result = count_occ(l1);

    print_occ(result, fptr);

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
