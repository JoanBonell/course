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
    pid_t pid;
    for(int i = 0; i < n_jugadores; i++){
        switch (pid)
        {
        case 0:
            printf("EscapeRoom[%d] ha entrat el jugador[%d]\n", getppid(), getpid());
            break;
        case -1:
            perror("Error fork() - pid \n");
            break;
        default:
            pid = fork();
            break;
        }
    }
    

}


