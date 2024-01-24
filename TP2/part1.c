/*
 * Ecole polytechnique de Montreal - GIGL
 * Automne  2023
 * Initlab - part1.c
 * 
 * ajoutez vos noms, prénoms, matricules et votre section de laboratoire
 */

// TODO
// Si besoin, ajouter ici les directives d'inclusion et les déclarations globales
// -------------------------------------------------

#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
   
// -------------------------------------------------

int main () {
    // TODO
    const int stdin = 0;
    const int stdout = 1;
    const int stderror = 2;

    int fd = open("output2.txt", O_WRONLY | O_TRUNC);

    if (fd < 0) {
        const char* errMsg = "Appel système open a échoué\n";
        write(stderror, errMsg, strlen(errMsg));
        return 0;
    }

    const char* msg = "Saisissez votre texte suivi de CTRL-D :\n";
    write(stdout, msg, strlen(msg));

    char* currentChar =  (char*)malloc(sizeof(char));
    int nBytes = 0;
    do {
        nBytes = read(stdin, currentChar, 1);
        write(fd, currentChar, strlen(currentChar));
    } while (nBytes != 0);

    int closeStatus = close(fd);


    if (closeStatus < 0) {
        const char* errMsg = "Appel système close a échoué\n";
        write(stderror, errMsg, strlen(errMsg));
        return 0;
    }


    return 0;
}
