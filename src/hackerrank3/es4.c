#include <stdio.h>
#include <stdlib.h>

unsigned long *create_n_fill_array(size_t size, unsigned long value) {
  printf("sizeof(size): %lu\n", sizeof(size));
  unsigned long *v = (unsigned long *)malloc(sizeof(size) * size);

  for (size_t i = 0; i < size; ++i) {
    v[i] = value;
  }

  return v;
}

// void log_array(const unsigned long *v, size_t size) {
//   for (size_t i = 0; i < size; ++i) {
//     printf("%lu ", v[i]);
//   }
//   printf("\n");
// }

void test_sizeof(void) {
  int myint = 2;
  unsigned int myuint = 2;
  unsigned long myulong = 2;
  printf("sizeof(myint): %lu | sizeof(int): %lu\n", sizeof(myint), sizeof(int));
  printf("sizeof(myuint): %lu | sizeof(unsigned int): %lu\n", sizeof(myuint), sizeof(unsigned int));
  printf("sizeof(myulong): %lu | sizeof(unsigned long): %lu\n", sizeof(myulong), sizeof(unsigned long));
}

int main(void) {
  test_sizeof();
  return 0;

  for (unsigned long i = 0; i < 100; i++) {
    unsigned long *arr_n = create_n_fill_array(100, i);
    free(arr_n);
    //     log_array(arr_n, 10000);
  }
  return 0;
}