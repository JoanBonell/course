#include <stdio.h>
#include <time.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include "jugador.h"
#define LONGITUD_PASSWD 4
int main(int argc, char *argv[]){
    if(argc <= 3){
        printf("Has de posar com a mínim 3 arguments\n");
        return 0;
    }
    
    int i = atoi(argv[2]); // Passem el string argv[2] a int i ho guardem a 'i'.
    int j = 0;
    pid_t pid[j];

    int pid_padre = getpid();
    printf("Inici del Room Escape [%d] (%s segons) \n", getpid(), argv[1]);
    printf("--- Entren %s jugadors a la sala \n", argv[2]);
    printf("--- La paraula a endevinar és = %s \n", argv[3]);

    //printf("EscapeRoom[pidpare] ha entrat el jugador[pidfill]\n");

    printf("********** DING DONG **********\n");
    printf("El jugador[pidfill] ha quedat atrapat i surt de EscapeRoom[pidpare]\n");
    printf("--- Els jugadors han perdut la partida. Fins aviat. \n");

    char destino[LONGITUD_PASSWD+1];
    cadena_aleatoria_byUs(destino);
    printf("Contrassenya aleatoria: %s\n", destino);

    //Necessitem:
    // Crear tants fills com argv[2]
    crear_jugadores(i, pid);
  
    printf("EscapeRoom[%d] ha entrat el jugador[%d]\n", pid, pid[j]);
    
    // Posar la contrassenya argv[3] dins del procés pare. //strcomp(CONTRASSENYAFILL, PARE);
    // Crear paraules aleatories de 4 caràcters per a cada fill i compararla amb la contrassenya del pare.

}



//Creamos un proceso
void crear_jugadores(int n_jugadores, pid_t *pid[]){
    for(int i = 0; i < n_jugadores; i++){
        pid[i] = fork();
    }
}