#include <stdio.h>

int main(){
    int d, k;
    scanf("%d", &d);
    scanf("%d", &k);

    for(int i = 0; i<k; i++){
        int tmp;
        scanf("%d", &tmp);

        if (tmp % d != 0) {
          /**
           * Interrompo l'esecuzione del programma al primo numero non divisibile
           * fornito dall'utente.
           * Questa è una scelta del programmatore nel momento in cui non vi
           * sono specifiche richieste del tipo "lasciar finire l'utente
           * prima di ritornare il risultato"
           */
            printf("false");
            return 0;
        }
    }

    printf("true");
}