// Standard IO library - Standard Input Output
#include <stdio.h>

/*
    This programs just prints "Hello world!"
    on your screen and terminates.
*/

void division(int a, int b) {
  printf("Division between %d and %d\n", a, b);
  printf("Result: %d\n", a/b);
  printf("Result: %d\n", a % b);
  printf("\n");
}

// You can assign variable values inside if statements.
void assignmentInIf(int a){
  printf("assignmentInIf with a = %d\n", a);
  if (a = 5) {
    printf("{if (a is 5)}\n");
  } else {
    printf("{else}\n");
  }

  printf("a is %d\n\n", a);
}

void prefixPostfix() {
  int a = 0;
  printf("prefixPostfix");
  printf("a is %d\n", a);
  printf("a++ is %d\n", a++);
  printf("a is %d\n", a);
  printf("++a is %d\n", ++a);
  printf("a is %d\n\n", a);
}

void prefiAssignment() {
  int a = 5;
  int b = 0;
  printf("Before: a is %d and b is %d\n", a, b);
  printf("b = ++a is %d\n", b = ++a);
  printf("Now: a is %d and b is %d\n\n", a, b);
}

void postfixAssignment() {
  int a = 5;
  int b = 0;
  printf("Before: a is %d and b is %d\n", a, b);
  printf("b = a++ is %d\n", b = a++);
  printf("Now: a is %d and b is %d\n\n", a, b);
}

void conditionalOperator(int a) {
  printf("conditionalOperator with a = %d | a == 1 ? \"a is true\" : \"a is false\": %s\n\n", a, a == 1 ? "a is true" : "a is false");
}

void operatorPrecedence() {
  int three(int print){
    if (print) printf("{three}\n");
    return 3;
  }

  int five(int print) {
    if (print) printf("{five}\n");
    return 5;
  }

  int ten(int print){
    if (print) printf("{ten}\n");
    return 10;
  }

  int two(int print){
    if (print) printf("{two}\n");
    return 2;
  }

  // NB you can always use "(" and ")" operators.
  // Yes, parentesis are operators.
  printf("3 + 5 * 10 / 2 => %d\n", three(0) + five(0) * ten(0) / two(0));
}

void multipleAssignments(){
  int x = 5 * 2; // 10
  int y = 2;
  int z = 3;
  printf("x=%d;y=%d,z=%d\n", x, y, z);
  // FIRST, y = z.
  // THEN x = (y = z) which equals to x = z;
  printf("x = y = z ==> %d\n", x = y = z);
  printf("x=%d;y=%d,z=%d\n\n", x, y, z);
}

void literals(){
  int intg0 = 7244ul;
  printf("int intg0 = 7244ul | intg0 = %d\n", intg0);
  int intg1 = 7244L;
  printf("int intg1 = 7244L | intg1 = %d\n", intg1);
  float float0 = 0.314;
  printf("float float0 = 0.314; | float0 = %f\n", float0);
  float float1 = .456;
  printf("float float1 = .456; | float1 = %f\n", float1);
  float float2 = -5.3e-11;
  printf("float float2 = -5.3e-11; | float2 = %f\n", float2);
}

/**
  Strings in C always end with "\0" character.
  You cannot define strings with single quotes.
*/
void charVsStringLiterals(){
  char a = 'a';
  char a0[] = "A";
  char* a1 = "A";
  printf("a = \"%c\"\n", a);
  printf("a0 = \"%s\"\n", a0);
  printf("a1 = \"%s\"\n", a1);

  /**
    Not a valid char.
    char a = 'Banana';
  */
}

int main() {
  printf("Hello world!\n");
  // division(10, 3);
  // assignmentInIf(5);
  // assignmentInIf(3);
  // prefixPostfix();
  // prefiAssignment();
  // postfixAssignment();
  // conditionalOperator(1);
  // conditionalOperator(0);
  // operatorPrecedence();
  // multipleAssignments();
  // literals();
  // charVsStringLiterals();
  return 0;
}
