#include <stdio.h>

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

void test_sort_desc(int *arr, int arr_size) {
  printf("Array prima dell'ordinamento: ");
  for (int i = 0; i < arr_size; i++) {
    printf("%d ", arr[i]);
  }

  sort_desc(arr, arr_size);

  printf("\nArray dopo l'ordinamento:     ");
  for (int i = 0; i < arr_size; i++) {
    printf("%d ", arr[i]);
  }

  printf("\n\n");
}

int main() {
  test_sort_desc((int[]){64, 25, 12, 22, 11}, 5);
  test_sort_desc((int[]){1, 2, 5, 60, 0}, 5);
  test_sort_desc((int[]){1, 2, 5, 60, 0}, 5);

  return 0;
}
