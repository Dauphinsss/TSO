#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main(){
    pid_t pid;
    int status;
    pid_t pids[5];
    for(int i = 0; i < 5; i++){
        pid = fork();
        if(pid < 0){
            exit(1);
        }else if(pid == 0){
            sleep(1);
            printf("hola soy el hijo %d\n", i +1);
            exit(0);
        }else{
            pids[i] = pid;
        }
        
    }
    for(int i = 0; i < 5; i ++){
            waitpid(pids[i], &status, 0);
        }
    printf("todos los hijos han terminado\n");
    return 0;
}
