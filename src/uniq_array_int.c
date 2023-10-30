// 30 ottobre 23

#include <stdio.h>
#include <stdlib.h>

// ************************* UNIQUE *************************
int *uniq(const int *arr, int arr_len, int *uniq_array_index) {
  int *result = malloc(sizeof(int) * arr_len);

  for (int i = 0; i < arr_len; i++) {
    const int current = arr[i];

    for (int j = 0; j < arr_len; j++) {
      if (current == arr[j]) {
        if (i == j) {
          result[(*uniq_array_index)++] = arr[i];
        }

        break;
      }
    }
  }

  result = realloc(result, sizeof(int) * *uniq_array_index);

  if (result == NULL) {
    printf("Error on realloc");
    exit(EXIT_FAILURE);
  }

  return result;
}

void run_uniq() {
  int uniq_arr_len = 0;
  int arr[8] = {1, 2, 3, 1, 4, 2, 3, -7};
  int *uniq_arr = uniq(arr, 8, &uniq_arr_len);

  for (int i = 0; i < 8; i++)
    printf("arr[%d] | %d\n", i, arr[i]);

  printf("\n");
  for (int i = 0; i < uniq_arr_len - 1 + 1; i++)
    printf("uniq_arr[%d] | %d\n", i, uniq_arr[i]);

  free(uniq_arr);
}

// ************************* DUPLICATE *************************
void only_twice(const int *arr, const int arr_size, int *new_arr,
                int *new_array_size) {

  for (int i = 0; i < arr_size; i++) {
    int count = 0;
    for (int j = 0; j < arr_size; j++) {
      if (arr[i] == arr[j])
        count++;
    }

    if (count >= 2)
      new_arr[(*new_array_size)++] = arr[i];

    printf("arr[%d] | is %d | count: %d\n", i, arr[i], count);
  }

//  printf("new_arr: ");
//  for(int i = 0; i < *new_array_size; i++)
//    printf("%d ", new_arr[i]);
//  printf("\n");

  int new_arr_size0 = 0;
  int *new_arr0 = uniq(new_arr, *new_array_size, &new_arr_size0);

  new_array_size = &new_arr_size0;
  new_arr = new_arr0;
}

void run_only_twice() {
  int arr_size = 8;
  int arr[8] = {1, 2, 3, 1, 4, 2, 3, -7};
  int *new_arr = malloc(sizeof(int) * arr_size);
  int new_arr_size = 0;
  only_twice(arr, arr_size, new_arr, &new_arr_size);

  for (int i = 0; i < arr_size; i++)
    printf("arr[%d] | %d\n", i, arr[i]);

  printf("\n");

  for(int i = 0; i < new_arr_size; i++)
    printf("new_arr[%d] | %d\n", i, new_arr[i]);
}

int main(void) {
  // run_uniq();
  run_only_twice();

  return 0;
}