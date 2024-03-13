
#include <semaphore.h>
#include <unistd.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <stdbool.h>
//..
int totalProduit = 0;
int totalConsomme = 0;
int tailleTampon;
static int* tampon;
int ip=0,ic=0;
// Semaphores
sem_t libre, occupe, mutexTampon, mutexProd, mutexCons;
bool flag_de_fin = false;

// fonction de nettoyage 
void mfree (void *arg)  {  printf("free\n"); free(arg); }

void* producteur(void* pid) {
    // ...
    int* somme = calloc( 1, sizeof(int) );
    *somme = 0;
    pthread_cleanup_push(mfree, (void*) somme);

    while(true) {
        sem_wait(&libre);
        sem_wait(&mutexTampon);
        tampon[ip] = (rand() % 9) + 1;
        *somme += tampon[ip];
        ip = (ip + 1) % tailleTampon;

        totalProduit++;

        sem_post(&mutexTampon);
        sem_post(&occupe);

        if(flag_de_fin) break;
    }


    pthread_cleanup_pop(0);

    printf("Fin Prod\n");

    pthread_exit(somme);
    return NULL;
}

void* consommateur(void* cid) {

    int* somme = calloc( 1, sizeof(int) );
    *somme = 0;

    pthread_cleanup_push(mfree, (void*) somme);

    int nombreTampon;

    while(true) {

        sem_wait(&occupe);
        sem_wait(&mutexTampon);
        nombreTampon = tampon[ic];
        *somme += nombreTampon;
        ic = (ic + 1) % tailleTampon;

        totalConsomme += nombreTampon == 0 ? 0: 1;

        sem_post(&mutexTampon);
        sem_post(&libre);

        //printf("nombreTampon: %d\n", nombreTampon);

        if (nombreTampon == 0) break;
    }

    pthread_cleanup_pop(0);

    printf("Fin Cons\n");

    pthread_exit(somme);
}

void action(int sig) {
    if (sig == SIGALRM ) {
        printf("Signal alarme\n");
        flag_de_fin = true;
    }
}

int main(int argc, char* argv[]) {
    // Les paramètres du programme sont, dans l'ordre :
    // le nombre de producteurs, le nombre de consommateurs
    // et la taille du tampon.

    srand ( time ( NULL ));

    const int np = atoi(argv[1]);
    const int nc = atoi(argv[2]);
    tailleTampon = atoi(argv[3]);

    // CONFIG ALARME
    signal(SIGALRM, action);

    tampon = calloc(tailleTampon, sizeof(int));

    sem_init(&libre, 0, tailleTampon);
    sem_init(&occupe, 0, 0);
    sem_init(&mutexTampon, 0, 1);

    sem_init(&mutexProd, 0, 1);
    sem_init(&mutexCons, 0, 1);

    pthread_t prods[np];
    pthread_t cons[nc];

    int pid[np];
    int cid[nc];

    // Create
    for(int i = 0; i < np; i++) {
        pid[i] = i;
        pthread_create(&prods[i], NULL, producteur, &pid[i]);
    }

    for(int i = 0; i < nc; i++) {
        cid[i] = i;
        pthread_create(&cons[i], NULL, consommateur, &cid[i]);
    }

    alarm(1);

    int sommeTotaleProd = 0;
    int* sommeProd;

    // Join producteurs
    for(int i = 0; i < np; i++) {
        pthread_join(prods[i], (void**) &sommeProd);
        sommeTotaleProd += *sommeProd;
    }

    mfree((void*) sommeProd);

    // remplir de 0 le tampon
    
    for(int i = 0; i < nc; i++) {
        sem_wait(&libre);
        sem_wait(&mutexTampon);
        tampon[ip] = 0;
        ip = (ip + 1) % tailleTampon;
        printf("ajoute 0 i: %d\n", i);
        sem_post(&mutexTampon);
        sem_post(&occupe);
    }


    int sommeTotaleCons = 0;
    int* sommeCons;
    // Join consommateurs
    for(int i = 0; i < nc; i++) {
        pthread_join(cons[i], (void**) &sommeCons);
        sommeTotaleCons += *sommeCons;
    }

    mfree((void*) sommeCons);

    printf("Somme des chiffres produits: %d\n", sommeTotaleProd);
    printf("Somme des chiffres consommes: %d\n", sommeTotaleCons);

    printf("Nombre de chiffres produits: %d\n", totalProduit);
    printf("Nombre de chiffres consommes: %d\n", totalConsomme);

    return 0;
}
