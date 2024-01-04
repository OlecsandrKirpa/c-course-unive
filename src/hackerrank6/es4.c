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

void print_list(list_t *l, FILE* fptr) {
       if (l) {
           fprintf(fptr, "%d ", l->data);
           print_list(l->next, fptr);
       } else
           fprintf(fptr, "\n");
}

void append(list_t *l, int elem) {
    list_t *new_elem = malloc(sizeof(list_t));
    new_elem->data = elem;
    new_elem->next = 0;

    l->next = new_elem;
}
/*
 * Complete the 'help_alessio' function below.
 *
 * The function accepts list_t **deck as parameter.
 */

void help_alessio(list_t **deck){
  // La prima carta del mazzo iniziale sarà di alberto,
  // perché la prima mossa di Alessio è ancora da aggiungere al mazzo.
  struct list* last = (*deck)->next;
  // Saltando di due in due per skippare la mossa che sarà di alberto.
  while(last && last->next && last->next->next){
    last = last->next->next;
  }

  // A questo punto last dovrebbe contenere l'ultima mossa di alessio.
  // Ed in base a quello bisognerà impostare la prima mossa.

  // first sarà la nuova testa della lista.
  list_t *first = (list_t*) malloc(sizeof(list_t));
  first->next = *deck;
  first->data = last->data;

  (*deck) = first;
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

    help_alessio(&l1);

    print_list(l1, fptr);

    fclose(fptr);

    return 0;
}

