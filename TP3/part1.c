/*
 * processlab - part1.c
 *
 * Ecole polytechnique de Montreal, GIGL, Hiver  2024
 * vos noms, prénoms et matricules
*/

#include "libprocesslab/libprocesslab.h"

// TODO
// Si besoin, ajouter ici les directives d'inclusion
// -------------------------------------------------
#include <unistd.h>
#include "./libprocesslab/libprocesslab.h"
// -------------------------------------------------

void question1()
{
   
    // TODO
    // level 0
    int status = 0;
    int totalChilds = 0;

    registerProc(getpid(), getppid(), 0, 0);

    if(fork() == 0) {
        // level 1.1
        registerProc(getpid(), getppid(), 1, 1);

        if(fork() == 0) {
            // level 2.1
            registerProc(getpid(), getppid(), 2, 1);
            _exit(0);
        }

        if(fork() == 0) {
            // level 2.2
            registerProc(getpid(), getppid(), 2, 2);
            _exit(0);
        }

        wait(NULL);
        wait(NULL);

        _exit(2);
    }

    if(fork() == 0) {
        // level 1.2
        registerProc(getpid(), getppid(), 1, 2);

        if(fork() == 0) {
            // level 2.3
            registerProc(getpid(), getppid(), 2, 3);
            _exit(0);
        }

        wait(&status);
        totalChilds += WEXITSTATUS(status);

        _exit(1);
    }

    if(fork() == 0) {
        // level 1.3
        registerProc(getpid(), getppid(), 1, 3);

        if(fork() == 0) {
            // level 2.4
            registerProc(getpid(), getppid(), 2, 4);
            _exit(0);
        }

        if(fork() == 0) {
            // level 2.5
            registerProc(getpid(), getppid(), 2, 5);
            _exit(0);
        }

        if(fork() == 0) {
            // level 2.6
            registerProc(getpid(), getppid(), 2, 6);
            _exit(0);
        }

        wait(NULL);
        wait(NULL);
        wait(NULL);

        _exit(3);
    }

    wait(&status);
    totalChilds += WEXITSTATUS(status);

    wait(&status);
    totalChilds += WEXITSTATUS(status);

    wait(&status);
    totalChilds += WEXITSTATUS(status);

    totalChilds += 3;

    printf("Nombre total de fils créés: %d\n", totalChilds);


    printProcRegistrations();

    execl("/usr/bin/ls", "ls", "-l", NULL);
}
