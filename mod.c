#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main() {
    pid_t pid1, pid2;
    int status1, status2;

    pid1 = fork();
    if (pid1 < 0) {
        perror("fork");
        exit(1);
    } else if (pid1 == 0) {
        sleep(5);
        exit(5);
    }

    pid2 = fork();
    if (pid2 < 0) {
        perror("fork");
        exit(1);
    } else if (pid2 == 0) {
        sleep(1);
        exit(1);
    }

    waitpid(pid1, &status1, 0);
    waitpid(pid2, &status2, 0);

    printf("Procesos hijos finalizados.\n");
    return 0;
}
