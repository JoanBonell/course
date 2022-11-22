/*  Jordi, et comentem que hem estat treballant juntament amb la Paula Silland..., tot i que no formi part del grup,
    per a que no creguis que hem fet dues pràctiques iguals copiant-les.
    Ens ha ajudat el següent video a fer això:
    https://www.youtube.com/watch?v=8LdQ09Ep9RY
*/

#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>
#include <signal.h>

#define READ_END    0    /* index pipe extremo lectura */
#define WRITE_END   1    /* index pipe extremo escritura */


#define FILE_NAME  "user.txt"   /* nombre del archivo donde escribir */

int main(int argc, char* argv[])   
{
    int fd1[2],fd2;
    int status, pid;
    
    pipe(fd1);                  /* comunica grep y passwd */
    
    switch(pid = fork()){
        case -1:
            perror("Error fork() - pid");
            return EXIT_FAILURE;
        case 0:
            close(fd1[READ_END]);   /* cerrar extremo no necesario */
        
            dup2(fd1[WRITE_END], STDOUT_FILENO); 
            close(fd1[WRITE_END]);
        
            execlp("/bin/grep", "grep", "$(whoami)", NULL);
    }
    

                              /* padre */
    
        close(fd1[WRITE_END]);    /* extremo no necesario ya */
        
        switch(pid = fork()){
            case -1:
                perror("Error fork() - pid");
                return EXIT_FAILURE;
            case 0:
                fd2 = open(FILE_NAME, O_WRONLY);
                dup2(fd1[READ_END], STDIN_FILENO);
                close(fd1[READ_END]);
		   		   
                dup2(fd2, STDOUT_FILENO);		   
            
                execlp("/etc/passwd",NULL);
        }
		
       
       
           close(fd1[READ_END]);      /* cerrar extremo no necesario */                  
    
   /* wait para cada hijo */
    wait(&status);   
    wait(&status);    
    
    return EXIT_SUCCESS;    
}