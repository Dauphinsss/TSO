#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main() {
    pid_t pid;
    int status;

    pid = fork();
    if (pid < 0) {
        perror("fork");
        exit(1);
    } else if (pid != 0) {
        while (pid != wait(&status));
    } else {
        sleep(5);
        exit(5);
    }

    pid = fork();
    if (pid < 0) {
        perror("fork");
        exit(1);
    } else if (pid != 0) {
        while (pid != wait(&status));
    } else {
        sleep(1);
        exit(1);
    }

    return 0;
}
