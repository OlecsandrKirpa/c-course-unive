#include <stdio.h>

struct point{
  float x;
  float y;
  char *label;
};


void print_a(struct point * p){
  printf("(%.3f, %.3f) -> %s\n", p->x, p->y, p->label);
}

void print_b(struct point * p){
  printf("(%.3f, %.3f) -> %s\n", (*p).x, (*p).y, p->label);
}

//void print_c(struct point * p){
//  printf("(%.3f, %.3f) -> %s\n", *p.x, *p.y, *p.label);
//}

//void print_d(struct point * p){
//  printf("(%.3f, %.3f) -> %s\n", (*p).x, (*p).y, *p.label);
//}

int main(void){
  struct point test={10, 20, "My Point"};
  struct point *test_p = &test;

  print_a(test_p);
  print_b(test_p);

  return 0;
}