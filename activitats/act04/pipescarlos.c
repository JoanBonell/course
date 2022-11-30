#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>


int main(int argc, char* argv[])   
{
    
    int fd1[2],fd2[2];
    int pid;
	
    pipe(fd1); /*Primera PIPE*/
    pid = fork();
    
    

    /*if(f1 == -1){
        perror("Error al obrir el fitxer");
        exit(1);
    }else if(f2 == -1){
        perror("Error al obrir el fitxer");
        exit(1);
    }*/

    
    if(pid == 0)              /* hijo 1*/
    {      		
        FILE *f1 = fopen("etc/passwd","r"); // Obre archiu per llegir.
        dup(fd1[1]); /*Redirecciona la salida estandar a la entrada de la pipe*/
        close(fd1[0]);
        execlp("/bin/grep","grep", "u",NULL);
        
        printf("Child PID is %d\n", getpid());

        char buff[100];
        read(fd1[0], buff, sizeof(buff));
        fclose(f1);
        
    }
    else if(pid > 0)          /* padre */
    {
        pipe(fd2); /*Segona PIPE*/
        pid = fork(); /*Segon fork*/
        if(pid == 0)          /* hijo 2*/
        {
            FILE *f2 = fopen("user.txt","a"); // Obre archiu per escriure amb APPEND.
            dup(fd2[0]); /*Redirecciona la entrada estandar a la salida de la pipe*/
            close(fd2[1]); /*Tanca el descriptor d'escriptura*/
           
            execlp("whoami","whoami",NULL);
            printf("Child PID is %d\n", getpid());
            fclose(f2);
            

        }
    }
    else {

        perror("fork");
        exit(1);
    }
    close(fd1[0]);
    close(fd1[1]);
    close(fd2[0]);
    close(fd2[1]);

    
    
    
    wait(NULL); /*Espera a que el fill acabi*/
    wait(NULL); /*Espera a que el fill acabi*/
    return 0;
  	
}