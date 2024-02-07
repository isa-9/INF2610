/*
 * processlab - part2.c
 *
 * Ecole polytechnique de Montreal, GIGL, Hiver  2024
 * vos noms, prénoms et matricules
*/

// TODO
// Si besoin, ajouter ici les directives d'inclusion
// -------------------------------------------------
#include <pthread.h> 
// -------------------------------------------------

#include "./libprocesslab/libprocesslab.h"

#define m 1000000
// question2 calcule la somme des m premiers nombres naturels 1+2+...+m

// nb est le nombre de threads qui vont contribuer au calcul
#define nb 4

//tableau somme est utilisé pour le calcul des sommes patielles par les threads
long somme[nb];


// fonction exécutée par chaque thread créé
void* contribution(void*p)
{
  // TODO
  int no = *((int*)p);
  somme[no] = 0;

  for(int i = no * m / nb + 1; i <= (no + 1) * m / nb; i++) {
    somme[no] += i;
  }

  pthread_exit(NULL);
}


void question2( )
{
  // TODO
  pthread_t *tid = calloc (nb , sizeof(pthread_t));

  int ordre[nb];
  for(int i = 0; i < nb; i++) {
    ordre[i] = i;
  }
  
  for(int i = 0; i < nb; i++) {
    pthread_create(&tid[i], NULL, contribution, &ordre[i]);
  }

  for(int i = 0; i < nb; i++) {
    pthread_join(tid[i],NULL);
  }

  long sommeTotale = 0;

  for(int i = 0; i < nb; i++) {
    sommeTotale += somme[i];
  }

  printf("SommeTotale: %ld, Valeur attendue: %ld\n", sommeTotale, m * (m + (long)1) / 2);
}
