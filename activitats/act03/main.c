#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>
#include <errno.h>

void launchcmd(char *arguments[]);
int
main(int argc, char *argv[]){
    // while not comand exit
        // readline
        // parseline
        // launch comand
        //Pid del padre
        int heacabat = 0;
        char* arguments;
        size_t nombrearguments;

        while(heacabat==0){
            getline(&arguments, &nombrearguments, stdin);
            arguments[strcspn(arguments, "\n")] = '\0';
            //nombrearguments = parseline(arguments);
            printf("%s\n",arguments);
            launchcmd(&arguments);
        }
}

void launchcmd(char** arguments){
    pid_t pid;
   // int st;
    pid = fork();
    if(pid == 0){
        
    
        if(execvp(arguments[0], **arguments)==-1){
            perror("Error.");
        }
        
    }
    else{
        wait(NULL);
       // waitpid(pid, &st, NULL);
    }
}