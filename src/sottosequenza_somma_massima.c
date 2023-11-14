#include <malloc.h>
#include <stdbool.h>

/**
 * Estremi inclusi.
 */
int somma_da_a(const int *arr, const int start_index, const int end_index) {
  int final = 0;
  for (int i = start_index; i <= end_index; i++)
    final += arr[i];

  return final;
}

/**
 * dato un array di interi,
 * trovare la sottosequenza di valori consecutivi
 * nell'array che ha somma massima e restituirne la somma
 */
int sottosequenza_somma_massima0(const int *arr, const int arr_len) {
  int max_sum = arr[0];
  int current_sum = 0;

  for (int i = 0; i < arr_len; i++) {
    const int current = arr[i];

    if (current >= 0) {
      current_sum += current;
      if (current_sum > max_sum)
        max_sum = current_sum;

      continue;
    }

    // current always < 0 from here
    current_sum = 0;
  }

  return max_sum;
}

int sottosequenza_somma_massima_recursive(const int *arr, const int arr_len, int max_sum, const int start_index, const int end_index){
  const int current_sum = somma_da_a(arr, start_index, end_index);
  if (max_sum < current_sum) max_sum = current_sum;

  printf("recursive | start_index: %d | arr_len: %d\n", start_index, arr_len);

  if (start_index >= arr_len - 1) return max_sum;

  return sottosequenza_somma_massima_recursive(arr, arr_len, max_sum, start_index + 1, end_index + 1);
}

int sottosequenza_somma_massima(const int *arr, const int arr_len){
  return sottosequenza_somma_massima_recursive(arr, arr_len, 0, 0, 0);

  int max_sum = arr[0];

  for(int i = 0; i < arr_len; i++){
    for(int j = i; j < arr_len; j++){
      const int current_sum = somma_da_a(arr, i, j);
      if (max_sum < current_sum) max_sum = current_sum;
    }
  }

  return max_sum;
}

bool all_tests_success = true;
int test_sottosequenza_massima_run_case(const int *arr, const int arr_len,
                                        const int expected, const int line) {
  const int result = sottosequenza_somma_massima(arr, arr_len);
  if (result == expected)
    return 0; // Everything fine. Test passed.

  printf("test_sottosequenza_massima_run_case failed at line %d | arr_len: %d "
         "| expected: %d | got: %d | array [",
         line, arr_len, expected, result);
  for (int i = 0; i < arr_len; i++) {
    printf("%d", arr[i]);
    if (i < arr_len)
      printf(", ");
  }

  printf("]\n");

  all_tests_success = false;

  return 1;
}

void test_sottosequenza_somma_massima(void) {
  const int arr0[] = {0, 10, 20, 30};
  test_sottosequenza_massima_run_case(arr0, 1, 0, __LINE__);
  test_sottosequenza_massima_run_case(arr0, 2, 10, __LINE__);
  return;
  test_sottosequenza_massima_run_case(arr0, 3, 10 + 20, __LINE__);
  test_sottosequenza_massima_run_case(arr0, 4, 10 + 20 + 30, __LINE__);

  const int arr1[] = {-30, 50, 10, 22};
  test_sottosequenza_massima_run_case(arr1, 4, 50 + 10 + 22, __LINE__);
  test_sottosequenza_massima_run_case(arr1, 2, 50, __LINE__);

  const int arr2[] = {-30, 50, -100, 10, 22};
  test_sottosequenza_massima_run_case(arr2, 5, 50, __LINE__);
  test_sottosequenza_massima_run_case(arr2, 1, -30, __LINE__);

  const int arr3[] = {100, -100, 100, -100, 10, 100, -500};
  test_sottosequenza_massima_run_case(arr3, 7, 110, __LINE__);

  const int arr4[] = {100, -100, 100, -100, 10, 100, -500};
  test_sottosequenza_massima_run_case(arr4, 7, 110, __LINE__);
  test_sottosequenza_massima_run_case(arr4, 1, 100, __LINE__);
  test_sottosequenza_massima_run_case(arr4, 6, 110, __LINE__);

  const int arr5[] = {101, -1, 101, -1, 101, -1};
  test_sottosequenza_massima_run_case(arr5, 6, 301, __LINE__);
}

int test_somma_da_a_run_case(const int *arr, const int arr_len,
                             const int start_index, const int end_index,
                             const int expected) {
  const int result = somma_da_a(arr, start_index, end_index);

  if (result == expected)
    return 0; // Everything fine. Test passed.

  printf("test_somma_da_a_run_case failed with | start_index: %d | end_index: "
         "%d | expected: %d | got: %d | array [",
         start_index, end_index, expected, result);
  for (int i = 0; i < arr_len; i++) {
    printf("%d", arr[i]);
    if (i < arr_len)
      printf(", ");
  }

  printf("]\n");

  all_tests_success = false;

  return 1;
}

void test_somma_da_a(void) {
  const int arr0[] = {0, 10, 20, 30};
  test_somma_da_a_run_case(arr0, 4, 0, 1, 10);

  const int arr1[] = {10, 20, 30};
  test_somma_da_a_run_case(arr1, 3, 0, 0, 10);
  test_somma_da_a_run_case(arr1, 3, 0, 2, 60);

  const int arr2[] = {101, -1, 101, -1, 101, -1};
  test_somma_da_a_run_case(arr2, 6, 0, 5, 300);
  test_somma_da_a_run_case(arr2, 6, 0, 0, 101);
  test_somma_da_a_run_case(arr2, 6, 0, 1, 100);
}

int main(void) {
  test_sottosequenza_somma_massima();
  test_somma_da_a();

  if (all_tests_success) {
    printf("Congratulations! All tests completed as expected!\n");
  }

  //  const int arr[] = {1, 5, 10, -4, 100};
  //  printf("sottosequenza massima per {1, 5, 10, -4, 100} è: %d\n",
  //         sottosequenza_somma_massima(arr, 5));
  return 0;
}