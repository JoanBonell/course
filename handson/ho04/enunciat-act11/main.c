#include <sys/wait.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include "pokemon.h"

pid_t pid;
int st;

void run_child(void);
void run_parent(void);

int
main(int argc, char *argv[])
{
}