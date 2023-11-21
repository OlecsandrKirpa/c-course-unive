#include <stdio.h>

int even_mult(int *a, size_t size) {
  int mult = 1;

  for (int i = 0; i < size; i += 2) {
    mult = mult * a[i];
    printf("index: %i | a[%d]: %d | mult: %i\n", i, i, a[i], mult);
  }

  return mult;
}

void test_even_mult(void) {
  int a[5] = {1, 2, 3, 4, 5};
  int mult = even_mult(a, 5);
  printf("mult: %d\n\n", mult);

  int b[6] = {1, 2, 3, 4, 5, 6};
  mult = even_mult(b, 6);
  printf("mult: %d\n\n", mult);

  int c[1] = {15};
  mult = even_mult(c, 1);
  printf("mult: %d\n\n", mult);

  int d[1] = {0};
  mult = even_mult(d, 1);
  printf("mult: %d\n\n", mult);

  int e[2] = {15, -1};
  mult = even_mult(e, 2);
  printf("mult: %d\n\n", mult);
}

int main(void) {
  test_even_mult();

  return 0;
}