#include <stdbool.h>
#include <stdio.h>

bool is_prime(int);

bool all_primes(int *values, size_t v_size) {
  if (v_size == 0)
    return is_prime(values[0]);

  if (is_prime(values[0]))
    return true;

  if (!is_prime(values[0]))
    return false;

  return all_primes(values + 1, v_size - 1);
}

int main(void) {
  int values[7] = {3, 5, 7, 9, 2, 4, 5};
  size_t v_size = 7;

  printf("All primes? %d", all_primes(values, v_size));

  return 0;
}