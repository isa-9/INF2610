#include <stdio.h>
//..
int totalProduit = 0;
int totalConsomme = 0;
int* tampon;
// Semaphores
//  -> Accès au
bool flag_de_fin = false;

void* producteur(void* pid) {
    // ...
    return NULL;
}

void* consommateur(void* cid) {
    // ...

    return NULL;
}
// ...

int main(int argc, char* argv[]) {
    // Les paramètres du programme sont, dans l'ordre :
    // le nombre de producteurs, le nombre de consommateurs
    // et la taille du tampon.

    int np = atoi(argv[1]);
    int nc = atoi(argv[2]);
    int tailleTampon = atoi(argv[3]);

    // ..
    return 0;
}
