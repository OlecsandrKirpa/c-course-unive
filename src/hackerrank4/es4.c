#include <stdbool.h>
#include <stdio.h>

bool not_equal(int a_zero, int ics){
  printf("not_equal: a_zero: %d | x: %d\n", a_zero, ics);
  return a_zero != ics;
}

bool not_contains(int *a, int a_size, int x) {
  printf("not_contains called with a_size: %d\n", a_size);
  if (a_size == 0)
    return true;


//  return (a[0] != x) && not_contains(a + 1, a_size - 1, x);
  return not_contains(a + 1, a_size - 1, x) && (a[0] != x);
//  return not_equal(a[0], x) && not_contains(a + 1, a_size - 1, x);
}

int main(void) {
  int a[10] = {0, 1, 2, 0, 4, 5, 0, 7, 8, 0};

//  printf("%d\n", not_contains(a, 10, 11)); // test 1
//  printf("%d\n", not_contains(a, 10, 2));  // test 2
//  printf("%d\n", not_contains(a, 10, 0));  // test 3
//  printf("%d\n", not_contains(a, 10, 10));  // test 4
}