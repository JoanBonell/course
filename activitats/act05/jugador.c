#include <stdio.h>
#include <time.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#define LONGITUD_PASSWD 4
void cadena_aleatoria_byUs(char **destino);
void acabar();

int main(int argc, char *argv[]){
    //crear paraula
    char* paraula_aleatoria = malloc(LONGITUD_PASSWD * sizeof(char));
    cadena_aleatoria_byUs(&paraula_aleatoria);
    printf("%s\n", paraula_aleatoria);fflush(stdout);

    //crear paraula mode 2
    char** paraules = malloc(1 * sizeof(char*));
    cadena_aleatoria_byUs2(paraules);
    printf("%s\n", paraules[0]);fflush(stdout);
    //definir senyal amb tractament
    signal(SIGUSR1, acabar);
    // escriure a 1
    while(1){

    }
    acabar();
}

void acabar(){
    exit(1);
}

//Generar paraula aleatoria desde 'a' fins a 'z' tot minúscules.
void cadena_aleatoria_byUs(char ** destino){
    srand(time(NULL));
    char aleatorio;
    char* word = malloc(LONGITUD_PASSWD * sizeof(char)); 
    for(int i = 0; i < LONGITUD_PASSWD;i++){
        aleatorio = 'a' + rand() % (('z'-'a')+1);
        word[i] = aleatorio;
    }
    printf("%s\n", word);fflush(stdout);
    *destino=word;
}

void cadena_aleatoria_byUs2(char ** destino){
    srand(time(NULL));
    char aleatorio;
    char* word = malloc(LONGITUD_PASSWD * sizeof(char)); 
    for(int i = 0; i < LONGITUD_PASSWD;i++){
        aleatorio = 'a' + rand() % (('z'-'a')+1);
        word[i] = aleatorio;
    }
    printf("%s\n", word);fflush(stdout);
    destino[0]=word;
}

