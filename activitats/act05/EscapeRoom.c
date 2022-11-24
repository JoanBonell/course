#include <stdio.h>
#include <time.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

void crear_jugadores(int n_jugadores, pid_t *pid[]);
int main(int argc, char *argv[]){
    /*  Per a fer servir el programa, l'usuari hauria de fer:
        ./sala arg1 arg2 arg3
        Per això, ens assegurarem que l'usuari ens passi 3 arguments
        de la següent manera, si no, atuarem directament el programa.*/
    if(argc <= 3){
        printf("Has de posar com a mínim 3 arguments\n");
        return 0;
    }

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

    
    while(jugant==1){
    // llegir de la pipe
    // per cada paraula llegida strcmp(argv[3])
    //
    }

    // Han guanyat
    for(int i = 0; i < n_jugadores; i++){
        kill(,SIGUS1);
    }
  

    // Esperant que acabin
    for(int i = 0; i < n_jugadores; i++){
        waitpid(pids[i],0,0);
    }

    

}


