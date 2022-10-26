#include <err.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int st;	

int main(int argc, char* argv[]){
    pid_t pid;
	//pid_t pid, w;
    int status;
    
    printf("Executant pare amb PID %d\n", pid);
    pid = fork(); // pid té un fill.
    if (pid == -1) {
        perror("fork");
        exit(EXIT_FAILURE);
    }
    if(pid == 0){
        wait(&st); //El pare espera al fill.
        printf("Executant fill amb PID %d\n", pid);
        fork(); //El fill té un altre fill (el net)
        if(pid==-1){
            perror("fork");
            exit(EXIT_FAILURE);
        }
        else if(pid == 0){
            wait(&st); // Fill espera net
            printf("Executant net amb PID %d\n",pid);
            printf("Acabant net amb PID %d\n",pid);
        }
        else{
            printf("Acabant fill amb PID %d\n",pid);
        }
    }
}