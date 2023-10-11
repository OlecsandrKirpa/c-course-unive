// Standard IO library - Standard Input Output
#include <stdio.h>

void division(int a, int b) {
    printf("Division between %d and %d\n", a, b);
    printf("Result: %d\n", a / b);
    printf("Result: %d\n", a % b);
    printf("\n");
}

// You can assign variable values inside if statements.
void assignmentInIf(int a) {
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
    printf("conditionalOperator with a = %d | a == 1 ? \"a is true\" : \"a is false\": %s\n\n", a,
           a == 1 ? "a is true" : "a is false");
}

int three(int print) {
    if (print) printf("{three}\n");
    return 3;
}

int five(int print) {
    if (print) printf("{five}\n");
    return 5;
}

int ten(int print) {
    if (print) printf("{ten}\n");
    return 10;
}

int two(int print) {
    if (print) printf("{two}\n");
    return 2;
}

void operatorPrecedence() {

    // NB you can always use "(" and ")" operators.
    // Yes, parentesis are operators.
    printf("3 + 5 * 10 / 2 => %d\n", three(0) + five(0) * ten(0) / two(0));
}

void multipleAssignments() {
    int x = 5 * 2; // 10
    int y = 2;
    int z = 3;
    printf("x=%d;y=%d,z=%d\n", x, y, z);
    // FIRST, y = z.
    // THEN x = (y = z) which equals to x = z;
    printf("x = y = z ==> %d\n", x = y = z);
    printf("x=%d;y=%d,z=%d\n\n", x, y, z);
}

void literals() {
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
void charVsStringLiterals() {
    char a = 'a';
    char a0[] = "A";
    char *a1 = "A";
    printf("a = \"%c\"\n", a);
    printf("a0 = \"%s\"\n", a0);
    printf("a1 = \"%s\"\n", a1);

    /**
      Not a valid char:
      char a = 'Banana';
    */
}

void logSizeOf() {
    printf("sizeof(1): %d\n", sizeof(1));
    printf("sizeof(4): %d\n", sizeof(4));
    printf("sizeof('C'): %d\n", sizeof('C'));
    printf("sizeof('a'): %d\n", sizeof('a'));
    printf("sizeof(1.1'): %d\n", sizeof(1.1));
    printf("sizeof(10ul'): %lf\n", sizeof(10ul));
}

void declareAndAssign() {
    int banana;
    banana = 2;
    printf("banana: %d\n", banana); // 2
    banana = 10;
    banana = 1.5; // wtf???
    printf("banana: %d\n", banana); // 1
    banana = 'g'; // WTFFFFFFF ????
    printf("banana: %d\n", banana); // 103
}

void overwriteConst() {
    const char BANANA = 'b';
    // BANANA = 'g'; // Uncomment to see error
    printf("banana %c\n", BANANA);

    /*
    #define char GANG = 'g';
    unsigned char;
    printf("gang: %c\n", GANG);
    GANG = 'b'; // WTF
    printf("gang: %c\n", GANG);
     */
}

void studentgrade() {
    printf("Enter student grade in American system\n");
    const char grade = getchar();
    printf("You entered: ");
    putchar(grade);
}

void scanfExample() {
    int myInt;
    float myFloat;
    char myChar;
    printf("Input please: [int] [float] [char]\n");
    scanf("%d %f %c", &myInt, &myFloat, &myChar);
    printf("myInt: %d\n", myInt);
    printf("myFloat: %f\n", myFloat);
    printf("myChar: %c\n", myChar);
}

void rettangolo() {
    printf("base: ");
    float base;
    scanf("%f", &base);
    printf("altezza: ");
    float altezza;
    scanf("%f", &altezza);
    printf("Base %f, altezza %f\n", base, altezza);

    const float perimetro = (base + altezza) * 2;
    const float area = base * altezza;
    printf("Perimetro %f, Area %f", perimetro, area);
}

void variablePointer() {
    int age = 12;
    // &age <-- is a pointer!
    // Reference to a pointer using %p

    // Pointer is something like 0x7ffe5367e044
    int *age_pointer = &age;
    printf("age: %d, &age(age pointer): %p; age_pointer is: %p\n", age, &age, age_pointer);

    char string = 'c';
    // Note that when you need to store the reference, you use the variable type and add an asterisk at the end.
    // If my variable is char, pointer will be char*
    char *string_pointer = &string;
    printf("string: %c, string_pointer: %p\n", string, string_pointer);

    float my_float;
    float *my_float_pointer = &my_float;
    printf("Unassigned variable | my_float: %f; &my_float: %p\n", my_float, &my_float);
    my_float = 9.2;
    printf("After assignment | my_float: %f, &my_float: %p\n", my_float, &my_float);

    // My pointer variable has itself a pointer!
    printf("Pointer | my_float_pointer: %p; &my_float_pointer: %p\n", my_float_pointer, &my_float_pointer);
}

void variableDereference() {
    int my_age = 43;
    int* age_pointer = &my_age;
    int *ptr = &my_age; // Pointer declaration
    printf("my_age: %d\n", my_age);
    printf("*&my_age: %d \n", *&my_age);

    printf("age_pointer: %p\n", age_pointer);
    printf("*ptr: %d \n", *ptr);
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
    // logSizeOf();
    // declareAndAssign();
    // overwriteConst();
    // studentgrade();
    // scanfExample();
    // rettangolo();
    // variablePointer();
    variableDereference();
    return 0;
}
