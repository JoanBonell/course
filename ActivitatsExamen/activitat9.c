#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

int main(){
    int status,pid; 
    int v = 0; 
    char buf[80]; 
    if(fork()==0){ // fill
        v=v+15; // v=15
        sprintf(buf,"v: %d\n",v); // v=15
        write(1,buf,strlen(buf)); // v=15
    }
    v=v+2; // v=2 (padre) v = 17 para el hijo
    pid=wait(&status);
    sprintf(buf,"pid: %d\n",pid); // pid = -1 (padre) pid = 0 (hijo)
    write(1,buf,strlen(buf)); 
    v=v+10; // v=12 (padre) v = 27 para el hijo
    sprintf(buf,"v: %d\n",v); // v=12 (padre) v = 27 para el hijo
    write(1,buf,strlen(buf)); 
    exit(0); 
}