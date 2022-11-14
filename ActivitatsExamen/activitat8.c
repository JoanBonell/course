#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

int main(){
    int st;
    switch (fork()){ // fill
        case 0: // fill
            printf("A");
            switch (fork()){ // net
                case 0:
                    printf("B"); // net
                    exit(0);
                default:
                    switch (fork()){ // net
                            case 0: // // net
                                printf("C");
                                exit(0);
                            
                            default: // fill
                                wait(&st);
                                exit(0);
                        }
                        wait(&st);
            }
        default: 
            wait(&st);
            exit(0);
    }
    
}