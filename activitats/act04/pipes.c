/*@authors:
    - Ricard Bosch Perianes ©
    - Joan Bonell Ruiz ©
    Pendent de fer: ús correcte de whoami encomptes de "root".
*/
#include <stdlib.h>
#include <stdio.h>
#include <signal.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <errno.h>

#define READ_END 0
#define WRITE_END 1

//  Hem mirat aquest video per fer això:
//  https://www.youtube.com/watch?v=8LdQ09Ep9RY

int main(int argc, char *argv[])
{
    int fd[2], fd1[2];
    FILE *fp;
    
    fp = fopen("user.txt", "a");

    int status;
    //Implement stdin and stdout < > and | pipes
    //https://www.youtube.com/watch?v=8LdQ09Ep9RY

    char *p1[] = {"grep", "root",NULL}; 
    char *p2[] = {"cat", "/etc/passwd", NULL}; 
    char *p3[] = {"$(whoami)", NULL};

    if (pipe(fd)<0){
        perror("Error de creació del pipe fd[]");
        return EXIT_FAILURE;
        /* NOTREACHED */
    }

    if(pipe(fd1)<0){
        perror("Error de creació del pipe fd1[]");
        return EXIT_FAILURE;
    }


    pid_t pid1, pid2, pid3;

    switch (pid2 = fork()){
        case -1:
            perror("Error fork() - pid1");
            return EXIT_FAILURE;
        case 0:
            // Fill -> whoami -> llegeix stdin i imprimeix a stdout
            // Tanquem stdin per llegir i redireccionem stdin per llegir de la pipe fd[0]
            dup2(fd1[1],STDOUT_FILENO);
            close(fd[1]);
            close(fd[0]);
            execvp(p3[0], p3);
            return EXIT_FAILURE;
        //default:
            // Pare -> cat -> llegeix stdin i imprimeix a stdout
            // Tanquem stdout per escriure i redireccionem stdout per escriure a la pipe fd[1]

            // NO CAL
            //waitpid(pid2, 0, 0);
            //p2[1] = malloc(sizeof(fd1[0]));
            //close(fd[1]);
            //close(fd[0]);
    }

    switch (pid1 = fork()){
        case -1:
            perror("Error fork() - pid1");
            return EXIT_FAILURE;
        case 0:
            // Fill -> grep whoami -> llegeix stdin -> imprimeix a stdout
            // Tanquem stdout i redireccionem stdout a l'escriptura fd[1] de la pipe
            dup2(fd[0],STDIN_FILENO);
            dup2(fileno(fp),STDOUT_FILENO);
            close(fd[1]);
            close(fd[0]);
            execvp(p1[0], p1);
            return EXIT_FAILURE;
    }
    switch(pid3 = fork()){
        case -1:
            perror("Error fork() - pid3");
            return EXIT_FAILURE;
        case 0:
            // Fill -> cat /etc/passwd -> llegeix argument -> imprimeix a stdout
            // Tanquem stdout i redireccionem stfout a la escriptura fd[1] de la pipe
            dup2(fd[1],STDOUT_FILENO);
            close(fd[1]);
            close(fd[0]);
            execvp(p2[0], p2);
            return EXIT_FAILURE;
    }
    close(fd[0]);
    close(fd[1]);
    close(fd1[0]);
    close(fd1[1]);
    waitpid(pid1,0,0);
    waitpid(pid2,0,0);
    waitpid(pid3, 0, 0);
    return EXIT_SUCCESS;
}
