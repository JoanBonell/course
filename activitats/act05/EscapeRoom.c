#include <stdio.h>
#include <time.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/wait.h>

void crear_jugadores(int n_jugadores, pid_t *pid[]);
int main(int argc, char *argv[]){
    /*  Per a fer servir el programa, l'usuari hauria de fer:
        ./sala arg1 arg2 arg3
        Per això, ens assegurarem que l'usuari ens passi 3 arguments
        de la següent manera, si no, atuarem directament el programa.*/
    /*if(argc <= 3){
        printf("Has de posar com a mínim 3 arguments\n");
        return 0;
    }*/
    /*  Només per a debuggar:*/
    argv[0] = "1";
    argv[1] = "2";
    argv[2] = "aaaa";

    /*  argv[2] = número de segons que volem que duri la partida com a màxim,
        passarem aquest string a int i ho guardarem a 'num_segons_partida'*/
    int num_segons_partida = atoi(argv[1]); // Passem el string argv[2] a int i ho guardem a 'num_segons_partida'.

    int n_jugadores = atoi(argv[2]);
    pid_t * pids = malloc(sizeof(pid_t) * n_jugadores);

    for(int i = 0; i < n_jugadores; i++){
        pids[i] = fork();
        switch (pids[i])
        {
        case 0:
            printf("EscapeRoom[%d] ha entrat el jugador[%d]\n", getppid(), getpid());
            //dup2
            //exec("jugador", NULL);
            break;
        case -1:
            perror("Error fork() - pid \n");
            break;
        }  
    }

    //Create a pipe
    int fd[2];
    if(pipe(fd) == -1){
        perror("Error de creació del pipe fd[]");
        return EXIT_FAILURE;
    }
    int jugant = 1;
    while(jugant==1){
    // llegir de la pipe
    //Read from the pipe
    char read_msg[80];
    read(fd[0], read_msg, sizeof(read_msg));
    printf("read %s",read_msg);
    //Write to the pipe
    char write_msg[80];
    fgets(write_msg, 80, stdin);
    write(fd[1], write_msg, strlen(write_msg)+1);
    }
    // per cada paraula llegida strcmp(argv[3])
    // enviar senyal fi. quan comparem argv[3] amb la paraula llegida
    

    // Han guanyat
    for(int i = 0; i < n_jugadores; i++){
        kill(0,SIGUSR1);
    }
  

    // Esperant que acabin
    for(int i = 0; i < n_jugadores; i++){
        waitpid(pids[i],0,0);
    }

    

}



