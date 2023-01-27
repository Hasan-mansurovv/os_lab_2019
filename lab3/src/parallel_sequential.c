#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <limits.h>


int main(int argc, char **argv)
{
    char filename[] = {"sequential_min_max"};
    //check for non-invalid arguments
    if (argc != 3)
    {
    printf("Usage: %s seed arraysize\n", argv[0]);
    return 1;
    }
    if (atoi(argv[1]) <= 0)
    {
        printf("seed is a positive number\n");
        return 1;
    }

    if (atoi(argv[2]) <= 0)
    {
        printf("array_size is a positive number\n");
        return 1;
    }
    char* av[] = {filename, argv[1], argv[2], NULL};

    //forking
    pid_t pid = fork();
    if(pid < 0) 
    {
        printf("unsuccessfull fork\n");
        return 1;
    }
    int count = 1;
    if (pid == 0)
    {
        execv("./sequential_min_max", argv);
        count = 0;
        return 0;
    }

    if(count)
    {
        int a = 0;
        wait(&a);
    }
    return 0;
}