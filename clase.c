#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {
    pid_t pid = fork(); 

    if (pid < 0) {
        perror("fork failed");
        return 1;
    }

    if (pid == 0) {
        execl("/bin/date", "date", (char *)NULL); 
        perror("execl failed");
        return 1;
    } else {
        int status;
        waitpid(pid, &status, 0);

        if (WIFEXITED(status)) {
            printf("El proceso hijo termino con estado: %d\n", WEXITSTATUS(status));
        }
    }

    return 0;
}
