#include <malloc.h>
#include <stdbool.h>
#include <stdio.h>

// Having hard-coded values is never a good practice.
// It's better to declare constants in the head of the file.
// If we decide our dangerous temperature is 60 instead of 50, we need to update
// it only here. Once. At the same time, if we want to see 4 times dangerous
// temperatures instead of 3, we need to update it only here. Once as well.
const int COUNT = 3;
const int TEMPERATURE_LIMIT = 50;

// Using global variables to keep the code clean;
// registered is initialized using COUNT value.
int *registered;
int write_index = 0;

// By resetting the write_index, even if our array registered has some values,
// we're going to just ignore them as they are not there.
void reset() { write_index = 0; }

// This function will add a temperature to our array.
void push(int temperature) {
  registered[write_index] = temperature;
  write_index++;
}

// Is there any danger?
bool danger() { return write_index > COUNT - 1; }

void print_fire() {
  printf("Fire!\n");
  for (int i = 0; i < COUNT; i++)
    printf("%d ", registered[i]);
}

// Using COUNT value to allocate the necessary memory for registered.
void initialize() { registered = malloc(sizeof(int) * COUNT); }

bool cannot_be_danger(const int total_numbers, const int a){
}

bool intervention_needed(const int k) {

  /**
   * If the given numbers will be less than the required number of dangerous
   * temperatures we already know there won't be any danger.
   *
   * Example: given numbers are 2.
   */
//  if (k < COUNT) return false;

  for (int i = 0; i < k; i++) {
    int temperature;
    scanf("%d", &temperature);
    temperature >= TEMPERATURE_LIMIT ? push(temperature) : reset();

    if (cannot_be_danger(k)) return false;
    if (danger()) return true;
  }

  return false;
}

void print_safe() {
  printf("No intervention needed\n");
}

int main() {
  initialize();
  int k;
  scanf("%d", &k);

  intervention_needed(k) ? print_fire() : print_safe();

  return 0;
}
