#include <err.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int status;
pid_t childPid;

int main(){
    pid_t pid;

    char *buffer = malloc(100*sizeof(char));
    sprintf(buffer, "Executant pare amb PID %d\n ", getpid());
    write(1, buffer, strlen(buffer));
    buffer = '\0';
    free(buffer);

    pid = fork();
    if(pid == 0){
        char *buffer = malloc(100*sizeof(char));
        sprintf(buffer, "Executant fill amb PID %d\n ", getpid());
        write(1, buffer, strlen(buffer));
        buffer = '\0';
        free(buffer);
        childPid = fork();
        if(childPid == 0){
            *buffer = malloc(100*sizeof(char));
            sprintf(buffer, "Executant net amb PID %d\n ", getpid());
            write(1, buffer, strlen(buffer));
            buffer = '\0';
            free(buffer);

            *buffer = malloc(100*sizeof(char));
            sprintf(buffer, "Acabant net amb PID %d \n", getpid());
            write(1, buffer, strlen(buffer));
            buffer = '\0';
            free(buffer);
            exit(0);
        }
        else{
            childPid = wait(&status);
            *buffer = malloc(100*sizeof(char));
            sprintf(buffer, "Acabant fill amb PID %d \n", getpid());
            write(1, buffer, strlen(buffer));
            buffer = '\0';
            free(buffer);
            exit(0);
        }
    }
    else{
        pid = wait(&status);
        char *buffer = malloc(100*sizeof(char));
        sprintf(buffer, "Acabant pare amb PID %d ", getpid());
        write(1, buffer, strlen(buffer));
        buffer = '\0';
        free(buffer);
        exit(0);
    }
}