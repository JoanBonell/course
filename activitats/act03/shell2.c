//Program a shell in C
//
//The shell must be able to execute the following commands:
//
//    cd: change directory
//    help: show the list of commands
//    exit: exit the shell
//
//The shell must be able to execute any other command that is in the PATH.
//
//The shell must be able to execute any command with its arguments.
//
//The shell must be able to execute any command in background.
//
//The shell must be able to execute any command in foreground.
//
//The shell must be able to execute any command in foreground and wait for it to finish.
//
//The shell must be able to execute any command in foreground and not wait for it to finish.
//
//The shell must be able to execute any command in background and wait for it to finish.
//
//The shell must be able to execute any command in background and not wait for it to finish.



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
char *builtin_str[] = {
    "cd",
    "help",
    "exit"
};
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

int shell_execute(char **args){
    int i;

    if(args[0] == NULL){
        return 1;
    }

    for(i = 0; i < shell_num_builtins(); i++){
        if(strcmp(args[0], builtin_str[i]) == 0){
            return (*builtin_func[i])(args);
        }
    }

    return shell_launch(args);
}

int shell_cd(char **args){
    if(args[1] == NULL){
        fprintf(stderr, "shell: expected argument to \"cd\"\n");
    }else{
        if(chdir(args[1]) != 0){
            perror("shell");
        }
    }
    return 1;
}

int shell_help(char **args){
    int i;
    printf("Shell by Marc Pons\n");
    printf("Type program names and arguments, and hit enter.\n");
    printf("The following are built in:\n");

    for(i = 0; i < shell_num_builtins(); i++){
        printf("  %s\n", builtin_str[i]);
    }

}

int shell_exit(char **args){
    return 0;
}

int shell_num_builtins(){
    return sizeof(builtin_str) / sizeof(char *);
}



int (*builtin_func[]) (char **) = {
    &shell_cd,
    &shell_help,
    &shell_exit
};

