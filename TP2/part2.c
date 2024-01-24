/*
 * Ecole polytechnique de Montreal - GIGL
 * Automne  2023
 * Initlab - part2.c
 *
 * ajoutez vos noms, prénoms et matricules
 * Isabella Santacuz 2204379, Michelle Nguyen 2212694
*/

#include <stdio.h>
#include <stdlib.h>
// Si besoin, ajouter ici les directives d'inclusion et les déclarations globales
// -------------------------------------------------
// TODO
#include <string.h>
#include <unistd.h>

// -------------------------------------------------
void part21 ()
{
 // TODO
    const char msg[] = "77dbcb01f571f1c32e196c3a7d26f62e (printed using printf)";
    for(int i = 0; i < strlen(msg); i++) {
        printf("%c", msg[i]);
    }


    write(1, "77dbcb01f571f1c32e196c3a7d26f62e (printed using write)\n", strlen("77dbcb01f571f1c32e196c3a7d26f62e (printed using write)\n"));

    printf("\n");
}

void part22 ()
{
 // TODO
    setvbuf(stdout, NULL, _IONBF, 0);

    part21();
}

int main (int argc, char* argv[])
{
    
    if (argc!=2)
    {   printf("Le programme a un seul paramètre : 1 ou 2\n");
        return 1;
    }
    switch (atoi(argv[1])) {
         case 1:        part21();
                        break;
         case 2:        part22();
                        break;
        default:        printf(" Le paramètre du programme est invalide\n");
                        return 1;
    }
    return 0;
}
