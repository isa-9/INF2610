
// Ajouter les directives d'inclusion nécessaires
#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/stat.h>

int main() {

    if (fork() == 0) { // P3
    int fd;
    mkfifo("tube2_3", 0600);

        if (fork() == 0) { // P2
            mkfifo("tube1_2", 0600);

            if (fork() == 0) { // P1
                fd = open("tube1_2", O_WRONLY);
                dup2(fd, 1);
                close(fd);

                execlp("cat", "cat", "In.txt", NULL);

                _exit(1);

            } else { // P2
                fd = open("tube1_2", O_RDONLY);
                dup2(fd, 0);
                close(fd);

                fd = open("tube2_3", O_WRONLY);
                dup2(fd, 1);
                close(fd);

                execlp("tr", "tr", "[a-z]", "[A-Z]", NULL);

                _exit(1);
            }
        } else { // P3
            fd = open("tube2_3", O_RDONLY);
            dup2(fd, 0);
            close(fd);

            int output = open("Outn.txt", O_WRONLY | O_CREAT | O_TRUNC, 0660);
            dup2(output, 1);
            close(output);
            
            execlp("diff", "diff", "-", "In.txt", NULL);

            _exit(1);
        }
    }

    while(wait(NULL) > 0) {}
}
