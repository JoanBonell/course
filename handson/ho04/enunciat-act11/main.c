#include <sys/wait.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include "pokemon.h"

int
main(int argc, char *argv[])
{
    /*Feu un fork de un pare i un fill, i el fill ha de fer el recobriment de l'executable.*/
    //Creamos un proceso padre:
    pid = fork();
    if(pid == -1){
        exit(-1);
    }
    else if(pid == 0){
        //Fill
        run_child();
    }
    else{
        //Pare
        run_parent();
    }

}

void run_child(){
    init_pokedex();
    if(){
        
    }
}

void run_parent(){

}