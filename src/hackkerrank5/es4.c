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

char *readline() {
  size_t alloc_length = 1024;
  size_t data_length = 0;

  char *data = malloc(alloc_length);

  while (1) {
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

#ifndef _DVECTOR_H_
#define _DVECTOR_H_

/** \mainpage Dynamic Vector
 *
 * This library implements a vector with dynamic size.
 *
 */

/**
 * Data type of the vector elements.
 */
typedef int vdata_t;

/**
 * The Dynamic Vector data type.
 */
typedef struct vector vector_t;

/**
 * Allocates an empty vector.
 * @return empty vector.
 */
vector_t *v_create();

/**
 * Clones a vector (deep copy).
 * @return vector.
 */
vector_t *v_clone(const vector_t *v);

/**
 * Frees a vector and the memory it uses.
 * @param v The vector to be freed.
 */
void v_free(vector_t *v);

/**
 * Prints a vector.
 * @param v The vector to be printed.
 */
void v_print(const vector_t *v);

/**
 * Checks if a vector is empty.
 * @param v The vector.
 * @return 1 if empty, 0 otherwise.
 */
int v_is_empty(const vector_t *v);

/**
 * Returns the size of a given vector.
 * @param v The vector.
 * @return The number of elements stored in the vector.
 */
size_t v_size(const vector_t *v);

/**
 * Returns element at a given index.
 * Program exits if index is out of bounds.
 * @param v The vector.
 * @param index The desired index.
 * @return the value stored at the corresponding index.
 */
vdata_t v_get(const vector_t *v, size_t index);

/**
 * Stores a value at a given index.
 * Program exits if index is out of bounds.
 * @param v The vector.
 * @param index The desired index.
 * @param value The value to be stored.
 */
void v_set(vector_t *v, size_t index, vdata_t value);

/**
 * Inserts a new value after the last element of the vector.
 * @param v The vector.
 * @param value The value to be inserted.
 */
void v_push_back(vector_t *v, vdata_t value);

/**
 * Removes the last element in the vector and returns its value.
 * Program exists if vector is empty.
 * @param v The vector.
 * @return The value previously stored in the last position.
 */
vdata_t v_pop_back(vector_t *v);

/**
 * Inserts a new value before the first element of the vector.
 * @param v The vector.
 * @param value The value to be inserted.
 */
void v_push_front(vector_t *v, vdata_t value);

/**
 * Removes the first element in the vector and returns its value.
 * Program exists if vector is empty.
 * @param v The vector.
 * @return The value previously stored in the first position.
 */
vdata_t v_pop_front(vector_t *v);

/**
 * Inserts a new value at given position by shifting existing elements to the
 * right. Program exits if index is out of bounds.
 * @param v The vector.
 * @param value The value to be inserted.
 * @param index The position where to insert the value.
 */
void v_insert_at(vector_t *v, vdata_t value, size_t index);

/**
 * Deletes element at given position by shifting existing elements to the left.
 * Program exits if index is out of bounds.
 * @param v The vector.
 * @param index The position to be removed.
 */
void v_delete_at(vector_t *v, size_t index);

#endif

/**
 * The Dynamic Vector data type
 */
struct vector {
  /** The number of elements in the vector */
  size_t size;
  /** The amount of allocated memory */
  size_t capacity;
  /** The allocated memory */
  vdata_t *data;
};

/**
 * The minimum allocated memory upon creation.
 */
const size_t V_MIN_CAPACITY = 16;

/**
 * Extends allocated memory if entirely used by the stored elements.
 * @param v The vector.
 */
void _v_check_extend(vector_t *v) {
  if (v->size == v->capacity) {
    vdata_t *new_data = (vdata_t *)realloc(
        v->data,
        v->capacity * 2 *
            sizeof(
                vdata_t)); /* see https://en.cppreference.com/w/c/memory/realloc
                            */
    if (!new_data) {
      v_free(v); /* This is a reminder that in case of error,
                  * the programmer is in charge of the original memory */
      printf("Error: Failed memory allocation\n");
      exit(EXIT_FAILURE);
    }
    v->data = new_data;
    v->capacity *= 2;
  }
}

/**
 * Shrinks allocated memory if larger than twice the number of stored elements.
 * @param v The vector.
 */
void _v_check_shrink(vector_t *v) {
  size_t half_capacity = v->capacity / 2;
  if (half_capacity >= V_MIN_CAPACITY && v->size <= half_capacity) {
    vdata_t *new_data = (vdata_t *)realloc(
        v->data,
        half_capacity *
            sizeof(
                vdata_t)); /* see https://en.cppreference.com/w/c/memory/realloc
                            */
    if (!new_data) {
      v_free(v); /* This is a reminder that in case of error,
                  * the programmer is in charge of the original memory */
      printf("Error: Failed memory allocation\n");
      exit(EXIT_FAILURE);
    }
    v->data = new_data;
    v->capacity = half_capacity;
  }
}

/**
 * Fatal exit if the given index is beyond vector size.
 * @param v The vector.
 * @param index The index.
 */
void _v_check_index(const vector_t *v, size_t index) {
  if (index >= v->size) {
    printf("Error: Index %lu out of bounds for vector of size %lu\n", index,
           v->size);
    exit(EXIT_FAILURE);
  }
}

/**
 * Fatal exit if the given vector is empty.
 * @param v The vector.
 */
void _v_check_non_empty(const vector_t *v) {
  if (v_is_empty(v)) {
    printf("Error: Empty vector\n");
    exit(EXIT_FAILURE);
  }
}

vector_t *v_create() {
  vector_t *v = (vector_t *)malloc(sizeof(vector_t));
  v->size = 0;
  v->capacity = V_MIN_CAPACITY; /* initial capacity */
  v->data = (int *)malloc(v->capacity * sizeof(vdata_t));
  if (!v->data) {
    printf("Error in memory allocation\n");
    exit(EXIT_FAILURE);
  }
  return v;
}

vector_t *v_clone(const vector_t *v) {
  vector_t *c = (vector_t *)malloc(sizeof(vector_t));
  c->size = v->size;
  c->capacity = v->capacity;
  c->data = (int *)malloc(c->capacity * sizeof(vdata_t));
  if (!c->data) {
    printf("Error in memory allocation\n");
    exit(EXIT_FAILURE);
  }
  memcpy(c->data, v->data, v->size * sizeof(vdata_t));

  return c;
}

void v_free(vector_t *v) {
  free(v->data);
  free(v);
}

void v_print(const vector_t *v) {
  size_t i;
  printf("[ ");
  for (i = 0; i < v->size; i++)
    printf("%d ", (int)v->data[i]);
  printf("]");
}

int v_is_empty(const vector_t *v) { return v->size == 0; }

size_t v_size(const vector_t *v) { return v->size; }

int v_get(const vector_t *v, size_t index) {
  _v_check_index(v, index);
  return v->data[index];
}

void v_set(vector_t *v, size_t index, vdata_t value) {
  _v_check_index(v, index);
  v->data[index] = value;
}

void v_push_back(vector_t *v, vdata_t value) {
  _v_check_extend(v);
  v->data[v->size++] = value;
}

int v_pop_back(vector_t *v) {
  vdata_t value;
  _v_check_non_empty(v);
  value = v->data[v->size - 1];
  v->size--;
  _v_check_shrink(v);
  return value;
}

void v_push_front(vector_t *v, vdata_t value) {
  size_t i;
  _v_check_extend(v);
  for (i = v->size; i > 0; i--)
    v->data[i] = v->data[i - 1];
  v->size++;
  v->data[0] = value;
}

int v_pop_front(vector_t *v) {
  size_t i;
  vdata_t value;
  _v_check_non_empty(v);
  value = v->data[0];
  for (i = 0; i < v->size; i++)
    v->data[i] = v->data[i + 1];
  v->size--;
  _v_check_shrink(v);
  return value;
}

void v_insert_at(vector_t *v, vdata_t value, size_t index) {
  size_t i;
  _v_check_index(v, index);
  _v_check_extend(v);
  for (i = v->size; i > index; i--)
    v->data[i] = v->data[i - 1];
  v->size++;
  v->data[index] = value;
}

void v_delete_at(vector_t *v, size_t index) {
  size_t i;
  _v_check_index(v, index);
  for (i = index; i < v->size; i++)
    v->data[i] = v->data[i + 1];
  v->size--;
  _v_check_shrink(v);
}

void read_int_array(vector_t *v) {
  char *line = ltrim(rtrim(readline()));
  char *pc = strtok(line, " ");
  while (pc != NULL) {
    v_push_back(v, parse_int(pc));
    pc = strtok(NULL, " ");
  }
}

void hr_out_vector(FILE *f, vector_t *a) {
  for (size_t i = 0; i < v_size(a); i++) {
    fprintf(f, "%d", v_get(a, i));
    if (i != v_size(a) - 1)
      fprintf(f, " ");
  }

  fprintf(f, "\n");
}

/*
 * Complete the 'dot_product' function below.
 *
 */

// long long dot_product(vector_t *a, vector_t *b) {
//   if (a->size == 0 || b->size == 0) return 0;
//
//   vector_t * a_next = v_clone(a);
//   vector_t * b_next = v_clone(b);
//
//   a_next->data++;
//   a_next->size--;
//
//   b_next->data++;
//   b_next->size--;
//
//   return *(a->data) * *(b->data) + dot_product(a_next, b_next);
// }

long long dot_product(vector_t *a, vector_t *b) {
  if (a->size == 0 || b->size == 0)
    return 0;

  return *(a->data) * *(b->data) +
         dot_product(
           &((vector_t){a->size - 1, a->capacity, a->data + 1}),
           &((vector_t){b->size - 1, b->capacity, b->data + 1})
        );
}

int main() {
  FILE *fptr = fopen(getenv("OUTPUT_PATH"), "w");

  vector_t *a = v_create();
  vector_t *b = v_create();

  read_int_array(a);

  read_int_array(b);

  long long res = dot_product(a, b);

  fprintf(fptr, "%lld\n", res);

  v_free(a);
  v_free(b);

  fclose(fptr);

  return 0;
}
