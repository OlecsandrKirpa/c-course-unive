
/*
 * PROBLEMA DEL RESTO
 * Dobbiamo dare al nostro cliente un resto di 𝑡 fiorini. Dato un insieme di
 * monete di diverso taglio, dire quanti modi possibili ci sono per scegliere un
 * sotto‑insieme di monete la cui somma sia pari al resto 𝑡. Siano dati un array
 * 𝑐 con i valori delle diverse monete, e un array 𝑞 con la quantità di monete
 * per ciascun taglio.
 */

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

int *copy_without_element_at_index(const int *arr, const int arr_size,
                                   const int index) {
  int *new_arr = malloc((arr_size - 1) * sizeof(int));

  int new_arr_index = -1;
  for (int i = 0; i < arr_size; i++) {
    new_arr_index++;

    if (i == index) {
      continue;
    }

    new_arr[new_arr_index] = arr[i];
  }

  return new_arr;
}

int *copy_array(const int *arr, const int arr_size) {
  int *new_arr = malloc(arr_size * sizeof(int));

  for (int i = 0; i < arr_size; i++) {
    new_arr[i] = arr[i];
  }

  return new_arr;
}

void log_cassa(const int *valori, const int *quantita, const int size) {
  for (int i = 0; i < size; i++) {
    if (quantita[i] == 0) {
      continue;
    }

    if (i > 0)
      printf("  +  ");
    //    printf("%d monete da %d fiorini\n", quantita[i], valori[i]);
    //    printf("%d monete da %d fiorini\n", quantita[i], valori[i]);
    printf("%d$ x %d", valori[i], quantita[i]);
    //    if (i < size - 1) printf(" + ");
  }

  printf("\n");
}

// void possibili_soluzioni(
//     /**
//      * Cosa ho in cassa:
//      * - Di che tagli sono le monete che ho in cassa
//      * - Quante monete ho per ogni taglio
//      */
//     const int *cassa_valori, int *cassa_quantita, const int cassa_size,
//
//     /**
//      * Quanto manca ancora da dare di resto
//      */
//     const int resto_mancante,
//
//     // TODO remove solutions variable.
//     int *solutions,
//
//     /**
//      * Numerosità di monete che ho dato al cliente per taglio.
//      * Funziona esattamente come cassa_quantità.
//      */
//     int *customer_quantity) {
//
//   if (resto_mancante < 0) {
//     printf("Resto minore di zero. %d\n", resto_mancante);
//     exit(EXIT_FAILURE);
//   }
//
//   if (resto_mancante == 0) {
//     (*solutions)++;
//     printf("Trovata la soluzione #%d\n", *solutions);
//     log_cassa(cassa_valori, customer_quantity, cassa_size);
//     return;
//   }
//
//   for (int i = 0; i < cassa_size; i++) {
////            printf("Considerando la moneta da %d fiorini.\n",
////            cassa_valori[i]);
//    if (cassa_quantita[i] == 0) {
//      continue;
//    }
//
//    const int taglio = cassa_valori[i];
//    if (taglio > resto_mancante) {
//      continue;
//    }
//
//    // Suppongo quindi di dare al cliente anche questa moneta.
//    cassa_quantita[i]--;
//    customer_quantity[i]++;
//
////    printf("Diamo al cliente una moneta da %d fiorini.\n", taglio);
////    printf("Cassa: \n");
////    log_cassa(cassa_valori, cassa_quantita, cassa_size);
//
//    possibili_soluzioni(cassa_valori, cassa_quantita, cassa_size,
//                        resto_mancante - taglio, solutions,
//                        customer_quantity);
//
//    customer_quantity[i]--;
//    cassa_quantita[i]++;
//  }
//
//  //  printf("Finito.\n");
//}

int **solutions = NULL;
int solutions_size = 0;

bool is_solution_already_registered(int *quantita, int size) {
  for (int i = 0; i < solutions_size; i++) {
    bool is_solution = true;
    for (int j = 0; j < size; j++) {
      if (solutions[i][j] != quantita[j]) {
        is_solution = false;
        break;
      }
    }

    if (is_solution) {
      return true;
    }
  }

  return false;
}

/**
 * Returns false if solution was already present.
 * True otherwise.
 */
bool register_solution(int *quantita, int size) {
  if (is_solution_already_registered(quantita, size)) {
    //    printf("Non registro la soluzione perché già presente\n");
    return false;
  }

  solutions = realloc(solutions, (solutions_size + 1) * sizeof(int *));
  if (solutions == NULL) {
    printf("Errore nell'allocazione della memoria.\n");
    exit(EXIT_FAILURE);
  }

  solutions[solutions_size] = malloc(size * sizeof(int));
  if (solutions[solutions_size] == NULL) {
    printf("Errore nell'allocazione della memoria.\n");
    exit(EXIT_FAILURE);
  }

  for (int i = 0; i < size; i++) {
    solutions[solutions_size][i] = quantita[i];
  }

  solutions_size++;
  return true;
}

int possibili_soluzioni(
    /**
     * Cosa ho in cassa:
     * - Di che tagli sono le monete che ho in cassa
     * - Quante monete ho per ogni taglio
     */
    const int *cassa_valori, int *cassa_quantita, const int cassa_size,

    /**
     * Quanto manca ancora da dare di resto
     */
    const int resto_mancante,

    /**
     * Numerosità di monete che ho dato al cliente per taglio.
     * Funziona esattamente come cassa_quantità.
     */
    int *customer_quantity) {
  //  printf("Chiamato la funzione | resto_mancante: %d | cassa: ",
  //  resto_mancante); log_cassa(cassa_valori, cassa_quantita, cassa_size);

  if (resto_mancante < 0) {
    printf("Resto minore di zero. %d\n", resto_mancante);
    exit(EXIT_FAILURE);
  }

  if (resto_mancante == 0) {
    /**
     * Trovato una soluzione!
     * Se è una nuova soluzione, aggiungo la soluzione all'array delle soluzioni
     * ed incremento il contatore delle soluzioni.
     * Se la soluzione è già presente, non la registro.
     */
    //    printf("Soluzione: ");
    //    log_cassa(cassa_valori, customer_quantity, cassa_size);
    //    printf("\n\n");

    return register_solution(customer_quantity, cassa_size);
  }

  int solutions_count = 0;
  for (int i = 0; i < cassa_size; i++) {
    //            printf("Considerando la moneta da %d fiorini.\n",
    //            cassa_valori[i]);
    if (cassa_quantita[i] == 0) {
      continue;
    }

    const int taglio = cassa_valori[i];
    if (taglio > resto_mancante) {
      continue;
    }

    // Suppongo quindi di dare al cliente anche questa moneta.
    cassa_quantita[i]--;
    customer_quantity[i]++;

    //    printf("Diamo al cliente una moneta da %d fiorini.\n", taglio);
    //    printf("Cassa: \n");
    //    log_cassa(cassa_valori, cassa_quantita, cassa_size);

    solutions_count +=
        possibili_soluzioni(cassa_valori, cassa_quantita, cassa_size,
                            resto_mancante - taglio, customer_quantity);

    customer_quantity[i]--;
    cassa_quantita[i]++;
  }

  return solutions_count;
}

void run_example(const int *cassa_valori, int *cassa_quantita,
                 const int cassa_size, const int resto_mancante,
                 const int expected_solutions) {
  int *customer_quantity = calloc(cassa_size, sizeof(int));

  solutions = calloc(1, sizeof(int *));
  solutions_size = 0;

  int solution = possibili_soluzioni(cassa_valori, cassa_quantita, cassa_size,
                                     resto_mancante, customer_quantity);
  if (solution != expected_solutions) {
    printf("[ERROR] Test at row %d failed. Expected %d, got %d\n", __LINE__,
           expected_solutions, solution);
  }

  //  for (int i = 0; i < solutions_size; i++) {
  //    printf("Soluzione #%d: ", i + 1);
  //    log_cassa(cassa_valori, solutions[i], cassa_size);
  //  }
}

void test_possibili_soluzioni(void) {
  run_example((int[]){1, 2, 5, 10, 20, 50, 100, 200},
              (int[]){1, 1, 1, 1, 1, 1, 1, 1}, 8, 10, 1);

  run_example((int[]){1, 2, 5, 10, 20, 50, 100, 200},
              (int[]){1, 1, 1, 1, 1, 1, 1, 1}, 8, 1, 1);

  run_example((int[]){1, 2, 5, 10, 20, 50, 100, 200},
              (int[]){2, 1, 1, 1, 1, 1, 1, 1}, 8, 2, 2);

  run_example((int[]){1, 2, 5, 10, 20, 50, 100, 200},
              (int[]){1, 1, 1, 1, 1, 1, 0, 1}, 8, 100, 0);

  run_example((int[]){1, 2, 5, 10, 20, 50, 100, 200},
              (int[]){1, 1, 1, 1, 1, 1, 1, 1}, 8, 100, 1);

  run_example((int[]){1, 2}, (int[]){2, 1}, 2, 2, 2);

  run_example((int[]){1, 2, 5, 10, 20, 50, 100, 200},
              (int[]){1, 1, 1, 1, 1, 1, 2, 2}, 8, 200, 2);

  run_example((int[]){1, 2, 5}, (int[]){3, 2, 1}, 3, 5, 3);
  run_example((int[]){1, 2, 5}, (int[]){10, 2, 1}, 3, 5, 4);
  run_example((int[]){1, 2, 5}, (int[]){10, 10, 1}, 3, 5, 4);
  run_example((int[]){1, 2, 5}, (int[]){10, 10, 10}, 3, 5, 4);

  run_example((int[]){1, 2, 5}, (int[]){10, 10, 10}, 3, 10, 10);
}

int main(void) {
  test_possibili_soluzioni();
  return 0;
}