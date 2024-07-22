#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main(){
    pid_t pid;
    int status;
    for(int i = 0; i < 5; i++){
        pid = fork();
        if(pid < 0){
            exit(1);
        }else if(pid == 0){
            sleep(2);
            printf("soy el proceso hijo %d\n",getpid());
        }else{
            wait(&status);
            printf("el proceso hijo %d ha finalizado",pid);
        }
    }
    return 0;
}
