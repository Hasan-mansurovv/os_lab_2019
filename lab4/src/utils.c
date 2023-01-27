#include "utils.h"

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <signal.h>
#include <sys/wait.h>
#include <unistd.h>



void GenerateArray(int *array, unsigned int array_size, unsigned int seed) {
  srand(seed);
  for (int i = 0; i < array_size; i++) {
    array[i] = rand();
  }
}

void KillYourChildren(int signo)
{
    int a = 0;
    pid_t b;
    printf("Waiting too long, killing processes\n");
    
    for(int i = 0; i < Gpnum; i++)
    {
        read(GPipeReadEnd, &b, sizeof(pid_t));
        kill(b, SIGKILL);
        waitpid(b, &a, WNOHANG);
        printf("%d/%d killed\n",i+1,Gpnum);
    }
    Gpnum = -1;
    return;
}