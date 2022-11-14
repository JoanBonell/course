#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

int main(){
    char msg[250]; int codret, pid;
    sprintf(msg, "Hola, sóc el pare amb pid %d", getpid());
    write(1, msg, strlen(msg));

    if(fork()==0){ // fill
        sprintf(msg, "Hola, sóc el fill amb pid %d", getpid());
        write(1, msg, strlen(msg));
        
        
        if(fork() == 0){ // net
            sprintf(msg, "Hola, sóc el net amb pid %d", getpid());
            write(1, msg, strlen(msg));
            sprintf(msg, "Adeu soc el net amb pid %d", getpid());
            write(1, msg, strlen(msg));
            exit(1);
        }
        pid = wait(&codret); // fill espera al net
        sprintf(msg, "Adeu soc el fill amb pid %d", getpid());
        write(1, msg, strlen(msg));
        exit(1);   
    }
    pid = wait(&codret); // pare espera al fill
    sprintf(msg, "Adeu soc el pare amb pid %d", getpid());
    write(1, msg, strlen(msg));
    exit(1);   
}