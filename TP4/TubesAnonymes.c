
// Ajouter les directives d'inclusion nécessaires
#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>

int main() {

    if (fork() == 0) { // P3
    int fd2_3[2];
    pipe(fd2_3);

        if (fork() == 0) { // P2
            dup2(fd2_3[1], 1);
            close(fd2_3[0]); close(fd2_3[1]);

            int fd1_2[2];
            pipe(fd1_2);

            if (fork() == 0) { // P1
                dup2(fd1_2[1], 1);
                close(fd1_2[0]); close(fd1_2[1]);

                execlp("cat", "cat", "In.txt", NULL);

                _exit(1);

            } else { // P2
                dup2(fd1_2[0], 0);
                close(fd1_2[0]); close(fd1_2[1]);

                execlp("tr", "tr", "[a-z]", "[A-Z]", NULL);

                _exit(1);
            }
        } else { // P3
            dup2(fd2_3[0], 0);
            close(fd2_3[0]); close(fd2_3[1]);

            int output = open("Out.txt", O_WRONLY | O_CREAT | O_TRUNC, 0660);
            dup2(output, 1);
            close(output);
            execlp("diff", "diff", "-", "In.txt", NULL);

            _exit(1);
        }
    }

    while(wait(NULL) > 0) {}
}
