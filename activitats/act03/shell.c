//JOAN BONELL RUIZ

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>
#include <errno.h>
#define SHELL_TOK_BUFSIZE 50
void shell_loop(void);
char *shell_read_line(void);
char **shell_split_line(char *line);
int shell_launch(char **args);
int shell_execute(char **args);
int shell_cd(char **args);
int shell_help(char **args);
int shell_exit(char **args);
int main(int argc, char **argv){
    shell_loop();
    return EXIT_SUCCESS;
}

void shell_loop(void){
    char *line;
    char **args;
    int status;

    do{
        printf("> ");
        line = shell_read_line();
        args = shell_split_line(line);
        status = shell_execute(args);

        free(line);
        free(args);
    }while(status);
}

char *shell_read_line(void){
    char *line = NULL;
    ssize_t bufsize = 0;
    getline(&line, &bufsize, stdin);
    if(!line){
        fprintf(stderr, "shell: allocation error");
        exit(EXIT_FAILURE);
    }
    return line;
}

char **shell_split_line(char *line){
    int bufsize = SHELL_TOK_BUFSIZE, position = 0;
    char **tokens = malloc(bufsize * sizeof(char*));
    char *token;

    if(!tokens){
        fprintf(stderr, "shell: allocation error");
        exit(EXIT_FAILURE);
    }

    token = strtok(line, SHELL_TOK_DELIM);
    while(token != NULL){
        tokens[position] = token;
        position++;

        if(position >= bufsize){
            bufsize += SHELL_TOK_BUFSIZE;
            tokens = realloc(tokens, bufsize * sizeof(char*));
            if(!tokens){
                fprintf(stderr, "shell: allocation error");
                exit(EXIT_FAILURE);
            }
        }

        token = strtok(NULL, SHELL_TOK_DELIM);
    }
    tokens[position] = NULL;
    return tokens;
}

int shell_launch(char **args){
    pid_t pid, wpid;
    int status;

    pid = fork();
    if(pid == 0){
        if(execvp(args[0], args) == -1){
            perror("shell");
        }
        exit(EXIT_FAILURE);
    }else if(pid < 0){
        perror("shell");
    }else{
        do{
            wpid = waitpid(pid, &status, WUNTRACED);
        }while(!WIFEXITED(status) && !WIFSIGNALED(status));
    }

    return 1;
}