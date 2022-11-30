#include <stdio.h>
#include <time.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/wait.h>

#define KNRM  "\x1B[0m"
#define KRED  "\x1B[31m"
#define KGRN  "\x1B[32m"
#define KYEL  "\x1B[33m"
#define KBLU  "\x1B[34m"
#define KMAG  "\x1B[35m"
#define KCYN  "\x1B[36m"
#define KWHT  "\x1B[37m"

void crear_jugadores(int n_jugadores, pid_t **pids);
int main(int argc, char *argv[]){
    char s[100];
    //Initialize *argv[] to ./jugador 1 2 aaaa
    
    /*  Per a fer servir el programa, l'usuari hauria de fer:
        ./sala arg1 arg2 arg3
        Per això, ens assegurarem que l'usuari ens passi 3 arguments
        de la següent manera, si no, atuarem directament el programa.*/
        //sprintf(s, "%sOh no!The pokemon broke free.%s\n", KBLU,KNRM);
    if(argc < 3){
        //sprintf(s, "Has de posar com a mínim 3 arguments\n", KRED, KNRM);
        perror("Error, mínim 3 arguments.\n");
        return EXIT_FAILURE;
    }
    /*  argv[1] = número de segons que volem que duri la partida com a màxim,
        passarem aquest string a int i ho guardarem a 'num_segons_partida'*/
    int num_segons_partida = atoi(argv[1]); // Passem el string argv[1] a int i ho guardem a 'num_segons_partida'.

    int n_jugadores = atoi(argv[2]); // Passem el string argv[2] a int i ho guardem a 'n_jugadores'.
    pid_t * pids = malloc(sizeof(pid_t) * n_jugadores); // Reservem memòria per a guardar els pid dels jugadors.
    //pipe(fd1); // Creem el pipe per a comunicar el pare amb el fill.
    //crear_jugadores(n_jugadores, &pids); // Creem els jugadors.
    for(int i = 0; i < n_jugadores; i++){
        pids[i] = fork(); // Creem un nou procés per a cada jugador.
        
        switch (pids[i]) // Comprovem si s'ha creat correctament.
        {
        case 0: // Si s'ha creat correctament, el procés fill executarà el programa jugador.
            printf("EscapeRoom[%d] ha entrat el jugador[%d]\n", getppid(), getpid());
            
            //dup2(, );
            //dup2
            //execl("./jugador", argv[3]);
            //dup2(fd1, fd2);
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
    execl("./jugador", argv[3]);
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



void crear_jugadores(int n_jugadores, pid_t **pids){
    char s[100];
    for(int i = 0; i < n_jugadores; i++){
        *pids[i] = fork(); // Creem un nou procés per a cada jugador.
        
        switch (*pids[i]) // Comprovem si s'ha creat correctament.
        {
        case 0: // Si s'ha creat correctament, el procés fill executarà el programa jugador.
            //setcolor(KBLU);
            // sprintf(s, "%sOh no!The pokemon broke free.%s\n", KBLU,KNRM);
            sprintf(s, "EscapeRoom[%d] ha entrat el jugador[%d]\n", getppid(), getpid(), KBLU, KNRM);
            
            //dup2(, );
            //dup2
            //execl("./jugador", argv[3]);
            //dup2(fd1, fd2);
            //exec("jugador", NULL);
            break;
        case -1:
            perror("Error fork() - pid \n");
            break;
        }  
    }
}