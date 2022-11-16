#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>
#include <errno.h>
#include "log.h"
#include <getopt.h> //Per a agafar els arguments de forma molt senzilla.

int main(int argc, char *argv[]){
    log_set_quiet(true); // No volem que ens mostri els missatges de log per defecte.
    int o;
    while((o = getopt(argc, argv, "-v"))!=EOF){
        switch(o){
            case 'v': //Si l'usuari ha posat -v
                log_set_quiet(false); // Mostrem els missatges
                break; 
        }
    }
}