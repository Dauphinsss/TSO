#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {
    pid_t pid;
    int i;

    for (i = 0; i < 3; i++) {
        pid = fork(); 
        if (pid < 0) {
            perror("fork failed");
            return 1;
        }

        if (pid == 0) {
            printf("Hijo %d, PID: %d\n", i + 1, getpid());
            return 0;
        }
    }

    for (i = 0; i < 3; i++) {
        int status;
        pid_t child_pid = wait(&status);
        if (WIFEXITED(status)) {
            printf("el proceso termino con estatus %d\n", WEXITSTATUS(status));
        }
    }

    printf("Todos los procesos han terminado.\n");

    return 0;
}
