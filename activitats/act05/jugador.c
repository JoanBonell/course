#include <stdio.h>
#include <time.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#define LONGITUD_PASSWD 4
void cadena_aleatoria_byUs(char **destino);
int main(int argc, char *argv[]){
    //crear paraula
    char *paraula_aleatoria = malloc(LONGITUD_PASSWD * sizeof(char));

    cadena_aleatoria_byUs(&paraula_aleatoria);
    printf("%s", paraula_aleatoria);
    //definir senyal amb tractament

    // escriure a 1
    while(1){}
}



//Generar paraula aleatoria desde 'a' fins a 'z' tot minúscules.
void cadena_aleatoria_byUs(char **destino){
    srand(time(NULL));
    char aleatorio;
    for(int i = 0; i < LONGITUD_PASSWD;i++){
        aleatorio = 'a' + rand() % (('z'-'a')+1);
        *destino[i] = aleatorio;
    }
}