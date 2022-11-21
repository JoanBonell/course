#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include "helpers.h"

int split_line(char *line, char* separator, char ***tokens){
    const size_t BUFFER_SIZE = 100;
    int i = 0;
    char **_tokens = *tokens;
    *tokens = malloc(sizeof(char*)*BUFFER_SIZE);
    char *token = malloc(sizeof(char)*BUFFER_SIZE);
    token = strtok(line, separator);
    while (token!=NULL)
    {
        token = strtok(NULL, separator);
        _tokens[i] = token;
        i++;
        if(i>=BUFFER_SIZE){
            BUFFER_SIZE += i;
            _tokens = realloc(_tokens, sizeof(char*)*BUFFER_SIZE);
        }
    }
    return i;
}
int read_line(char** line){
    size_t s_buffer;
    if(getline(line, &s_buffer, stdin) == -1){
        perror("readline():getline");
        return -1;
    }
    return 0;
}