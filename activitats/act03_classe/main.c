#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>
#include <errno.h>
#include "log.h"
#include <getopt.h> //Per a agafar els arguments de forma molt senzilla.
void launch(char* cmd);

int main(int argc, char *argv[]){
    log_set_quiet(true); // No volem que ens mostri els missatges de log per defecte.
    int o;
    while((o = getopt(argc, argv, "-v"))!=EOF){
        switch(o){
            case 'v': //Si l'usuari ha posat -v
                log_set_quiet(false); // Mostrem els missatges
                break; 
        }
    }
    int status = 0;
    do{
        printf("ossh> ");
        char *line = NULL;

    }while(status == 0);
}

void launch(char* cmd){
    char **child_proc = NULL;
    int n_child_proc = split_line(cmd, "|", &child_proc);
    int n_pipes = n_child_proc - 1;
    int **pipes;
    pipes = malloc(sizeof(int*)*n_pipes);//ESTEM AQUI
    if(n_pipes>0){
        for(int p = 0; p < n_pipes; p++)
            pipes[p] = malloc(2);
    }


    pid_t pid;
    pid = fork();
    if(pid==0){
        //Child
        char **args = NULL;
        int n_args = split_line(cmd, " ", &args);
        if(n_args>0)
            execvp(args[0], args);
    }
    else{
        int st;
        waitpid(pid, &st, 0);
        perror("launch():fork");
    }

}
/*void launch(char* line){
    pid_t pid;
    pid = fork();
    if(pid == 0){
        //Child process
        if(execlp(line, line, NULL) == -1){
            perror("launch():execlp");
        }
        exit(EXIT_FAILURE);
    }else if(pid < 0){
        //Error forking
        perror("launch():fork");
    }else{
        //Parent process
        do{
            w = waitpid(pid, &status, WUNTRACED);
        }while(!WIFEXITED(status) && !WIFSIGNALED(status));
    }
}*/