#include <malloc.h>
#include <stdbool.h>

/**
 * dato un array di interi,
 * trovare la sottosequenza di valori consecutivi
 * nell'array che ha somma massima e restituirne la somma
 */
int sottosequenza_somma_massima(const int *arr, const int arr_len) {
  return 10;
}

bool all_tests_success = true;
int run_case(const int *arr, const int arr_len, const int expected) {
  const int result = sottosequenza_somma_massima(arr, arr_len);
  if (result == expected)
    return 0; // Everything fine. Test passed.

  printf("Test failed with | arr_len: %d | expected: %d | got: %d | array [",
         arr_len, expected, result);
  for (int i = 0; i < arr_len; i++) {
    printf("%d", arr[i]);
    if (i + i < arr_len)
      printf(", ");
  }

  printf("]\n");

  all_tests_success = false;

  return 1;
}

void test_sottosequenza_somma_massima(void) {
  const int arr0[] = {0, 10, 20, 30};
  run_case(arr0, 4, 10 + 20 + 30);

  const int arr1[] = {-30, 50, 10, 22};
  run_case(arr1, 4, 50 + 10 + 22);

  const int arr2[] = {-30, 50, -100, 10, 22};
  run_case(arr2, 5, 50);

  const int arr3[] = {100, -100, 100, -100, 10, 100, -500};
  run_case(arr3, 7, 110);

  const int arr4[] = {100, -100, 100, -100, 10, 100, -500};
  run_case(arr4, 7, 110);

  if (all_tests_success){
    printf("Congratulations! All tests completed as expected!\n");
  }
}

int main(void) {
  test_sottosequenza_somma_massima();
  return 0;
}