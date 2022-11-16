#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include "helpers.h"

int split_line(char *line, char* separator, char ***tokens){
    int i = 0;
    char *token;
    char **tokens_aux = NULL;
    token = strtok(line, separator);
    while(token != NULL){
        tokens_aux = realloc(tokens_aux, sizeof(char*) * (i+1));
        if(tokens_aux == NULL){
            fprintf(stderr, "Error: %s\n", strerror(errno));
            return -1;
        }
        tokens_aux[i] = token;
        i++;
        token = strtok(NULL, separator);
    }
    return 0;
}
int read_line(char** line){
    size_t s_buffer;
    if(getline(line, &s_buffer, stdin) == -1){
        perror("readline():getline");
        return -1;
    }
    return 0;
}