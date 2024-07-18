#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main() {
    pid_t pid1, pid2;
    int status1, status2;

    // Crear el primer proceso hijo
    pid1 = fork();
    if (pid1 < 0) {
        perror("fork");
        exit(1);
    } else if (pid1 == 0) {
        // Código del primer proceso hijo
        sleep(5);
        exit(5);
    }

    // Crear el segundo proceso hijo
    pid2 = fork();
    if (pid2 < 0) {
        perror("fork");
        exit(1);
    } else if (pid2 == 0) {
        // Código del segundo proceso hijo
        sleep(1);
        exit(1);
    }

    // El proceso padre espera por la finalización de ambos procesos hijos
    // Utilizamos waitpid para esperar por cada hijo individualmente
    waitpid(pid1, &status1, 0);
    waitpid(pid2, &status2, 0);

    printf("Procesos hijos finalizados.\n");
    return 0;
}
