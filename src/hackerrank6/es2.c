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

struct list {
  int data;
  struct list *next;
};

typedef struct list list_t;

void append(list_t *l, int elem) {
  list_t *new_elem = malloc(sizeof(list_t));
  new_elem->data = elem;
  new_elem->next = 0;

  l->next = new_elem;
}

void insert_rec(list_t *l, int elem, int pos) {
  // Base case: I need to insert here
  if (pos == 0) {
    append(l, elem);
    return;
  }

  // if pos is odd then skip one
  if (pos % 2 == 1 && l->next != NULL) {
    insert_rec(l->next, elem, pos - 1);
    return;
  }

  // if pos is even then skip two
  if (pos % 2 == 0 && l->next != NULL && l->next->next != NULL) {
    insert_rec(l->next->next, elem, pos - 2);
    return;
  }

  // We are at the end of the list
  append(l, elem);
}

void print_list(list_t *l, FILE *fptr) {
  if (l) {
    fprintf(fptr, "%d ", l->data);
    print_list(l->next, fptr);
  } else
    fprintf(fptr, "\n");
}

int main(void) {
  list_t * lista = malloc(sizeof(list_t));
  lista->data = 1;
  append(lista, 2);
  append(lista->next, 3);
  append(lista->next->next, 4);
  append(lista->next->next->next, 5);

  printf("BEFORE\n");
  print_list(lista, stdout);

  insert_rec(lista, 20, 0);

  printf("AFTER\n");
  print_list(lista, stdout);

  return 0;
}

//int main(void) {
//  list_t * lista = malloc(sizeof(list_t));
//  lista->data = 15;
//  append(lista, 10);
//
//  printf("BEFORE\n");
//  print_list(lista, stdout);
//
//  insert_rec(lista, 20, 4);
//
//  printf("AFTER\n");
//  print_list(lista, stdout);
//
//  return 0;
//}