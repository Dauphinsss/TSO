#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define mensaje "Esto esta siendo enviado"

int main() {
    int pipefd[2];
    pid_t pid;
    char cadena[50];

    if (pipe(pipefd) == -1) {
        perror("fallo el pipe");
        return 1;
    }
  
    pid = fork();

    if (pid < 0) {
        perror("fork fallo");
        return 1;
    }

    if (pid == 0) {
        close(pipefd[1]);
        read(pipefd[0], cadena, sizeof(cadena));
        printf("Mensaje recibido: %s\n", cadena);
        close(pipefd[0]);
    } else {
        close(pipefd[0]);
        write(pipefd[1], mensaje, sizeof(mensaje));
        close(pipefd[1]);
        wait(NULL);
    }

    return 0;
}
