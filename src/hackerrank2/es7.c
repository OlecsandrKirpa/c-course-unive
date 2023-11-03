#include <stdio.h>
#include <string.h>
#include <stdbool.h>

/**
 * L'idea è la seguente:
 * Ci iteriamo i caratteri dall'inizio e dalla fine del nostro numero
 * e confrontiamo i caratteri con la stessa distanza dall'inizio e dalla fine.
 * Se i due caratteri alla stessa distanza non sono uguali, la cifra non è palindroma.
 */
bool is_palindrome(int num) {
    if (num <= 0) return false;

    char str[sizeof(int) * 4];
    snprintf(str, sizeof(str), "%d", num);
    int str_length = (int) strlen(str);

    for (int i = 0; i < str_length; i++) {
        int last_char_index = (str_length - 1) - i;

        if (str[i] != str[last_char_index]) return false;
    }

    return true;
}

int main() {
    int k;
    scanf("%d", &k);

    for(int i = 0; i < k; i++){
        int tmp;
        scanf("%d", &tmp);

        // Si interrompe l'utente mentre sta ancora inserendo i numeri appena ne
        // inserisce uno palindromo.
        // Questa è una scelta discutibile ma laddove non vi sono specifiche richieste
        // sta al programmatore decidere.
        if (is_palindrome(tmp)) {
            printf("false");
            return 0;
        }
    }

    printf("true");

    return 0;
}