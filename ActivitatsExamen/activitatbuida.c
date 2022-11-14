#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

#define W(x) write (1, #x, sizeof #x)
int main(){
    /*char msg[250];
    sprintf(msg, "T");
    int a = 3;
    int codret, pid;
    write(1, msg, strlen(msg)); //stdout = T
    if(fork()==0){
        a = a +2;
        sprintf(msg, "%sG", msg);
        write(1, msg, strlen(msg));
        exit(a);
    }
    pid = wait(&codret);
    sprintf(msg, "%sR", msg, WEXITSTATUS(codret));
    write(1, msg, strlen(msg));
    exit(1);*/
    //int n;
    // How many times process are going to be maken?

    //for(int i = 0, i < n; i++){//
      //  fork(); // Create a new process
    //}
    //What is the stdout of this program?
    // The STDOUT is: TGR
    //What is the value of a in the parent process?
    //What is the value of a in the child process?
    //What is the value of codret in the parent process?
    //What is the value of codret in the child process?
    char ptr [8] = "hola"; // 4 bytes

    char * ptr1 = ptr; // what is that? direccion de memoria

    char * ptr2 = malloc(4*sizeof(char)); //what is that? direccion de memoria

    ptr2 = strdup(ptr); //what is that? direccion de memoria

    //Comando para matar un proceso en c:
    //kill(pid, SIGKILL);
    //kill -9 pid
    //Comando para ver los procesos que se estan ejecutando:
    //ps -ef


    

}