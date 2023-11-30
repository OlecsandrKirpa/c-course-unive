#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void manipulation(char *s) {
  size_t i, b;
  b = strlen(s);
  for (i = 0; i < strlen(s); ++i) {
    if (*(s + i) == '!') {
      int c = 0;
      while (i + c + 1 < b && *(s + i + c + 1) == '!') {
        c++;
      }
      for (size_t k = i + 1; k < b - c && c > 0; ++k) {
        *(s + k) = *(s + k + c);
      }
      b -= c;
    }
  }
  // realloc omitted, memory management is in charge of the caller
  s[b] = '\0';
}

int main(void)
{
    char s[] = "!!He!llo!!! !";

    manipulation(s);
    printf("%s\n", s);

    return 0;
}