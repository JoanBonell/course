#include <err.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int st;	

int main(int argc, char* argv[]){
    pid_t pid, pid_child;
	//pid_t pid, w;
    int status;
    
    
    pid = fork(); // pid té un fill.
    if(pid !=0)
        printf("Executant pare amb PID %d\n", getpid());
    wait(&st); //El pare espera al fill.
    
    if (pid == -1) {
        perror("fork");
        exit(EXIT_FAILURE);
    }
    if(pid == 0){
        pid_child = fork(); //El fill té un altre fill (el net)
        printf("Executant fill amb PID %d\n", getpid());
        wait(&st); // Fill espera net
        printf("Acabant fill amb PID %d\n",getpid());
        if(pid==-1){
            perror("fork");
            exit(EXIT_FAILURE);
        }
        else if(pid == 0){
            printf("Executant net amb PID %d\n",getpid());
            printf("Acabant net amb PID %d\n",getpid());
        }
    }
    printf("Acabant pare amb PID %d\n", getpid());
    return EXIT_SUCCESS;
}