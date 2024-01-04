#include <stdio.h>

struct cat {
    char* name;
    int age;
};

struct person {
    char* name;
    int age;
    struct cat *cat;
};

void cat_swap(struct person* p1, struct person* p2){
    struct cat temp_cat = {p1->cat->name, p1->cat->age};

    p1->cat = p2->cat;
    p2->cat = &temp_cat;
}

int main(void){
  struct cat tom = {"Tom", 11};
  struct person sasha = {"Sasha", 21, &tom};
  struct cat oreste = {"Oreste", 2};
  struct person aurora = {"Aurora", 20, &oreste};

  printf("Before swap\n");
  printf("%s ha il gatto %s\n", sasha.name, sasha.cat->name);
  printf("%s ha il gatto %s\n", aurora.name, aurora.cat->name);

  cat_swap(&sasha, &aurora);

  printf("After swap\n");
  printf("%s ha il gatto %s\n", sasha.name, sasha.cat->name);
  printf("%s ha il gatto %s\n", aurora.name, aurora.cat->name);

  return 0;
}