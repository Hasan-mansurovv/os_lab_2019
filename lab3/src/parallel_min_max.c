#include <ctype.h>
#include <limits.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include <sys/time.h>
#include <sys/types.h>
#include <sys/wait.h>

#include <getopt.h>

#include "find_min_max.h"
#include "utils.h"

int main(int argc, char **argv) {
  int seed = -1;
  int array_size = -1;
  int pnum = -1;
  bool with_files = false;

  while (true) {
    int current_optind = optind ? optind : 1;

    static struct option options[] = {{"seed", required_argument, 0, 0},
                                      {"array_size", required_argument, 0, 0},
                                      {"pnum", required_argument, 0, 0},
                                      {"by_files", no_argument, 0, 'f'},
                                      {0, 0, 0, 0}};

    int option_index = 0;
    int c = getopt_long(argc, argv, "f", options, &option_index);

    if (c == -1) break;

    switch (c) {
      case 0:
        switch (option_index) {
          case 0:
            seed = atoi(optarg);
            // your code here
            // error handling
            if (seed <= 0) {
                printf("seed is a positive number\n");
                return 1;
            }
            break;
          case 1:
            array_size = atoi(optarg);
            // your code here
            // error handling
            if (array_size <= 0) {
                printf("array_size is a positive number\n");
                return 1;
            }
            break;
          case 2:
            pnum = atoi(optarg);
            // your code here
            // error handling
            if (pnum <= 0) {
                printf("pnum is a positive number\n");
                return 1;
            }
            if(pnum > array_size){
                printf("pnum must be less than array_size\n");
                pnum = array_size;
                printf("pnum is equal to array_size now (%d)\n", array_size);
            }
            break;
          case 3:
            with_files = true;
            break;

          defalut:
            printf("Index %d is out of options\n", option_index);
        }
        break;
      case 'f':
        with_files = true;
        break;

      case '?':
        break;

      default:
        printf("getopt returned character code 0%o?\n", c);
    }
  }

  if (optind < argc) {
    printf("Has at least one no option argument\n");
    return 1;
  }

  if (seed == -1 || array_size == -1 || pnum == -1) {
    printf("Usage: %s --seed \"num\" --array_size \"num\" --pnum \"num\" \n",
           argv[0]);
    return 1;
  }

  int *array = malloc(sizeof(int) * array_size);
  GenerateArray(array, array_size, seed);
  int active_child_processes = 0;

  struct timeval start_time;
  gettimeofday(&start_time, NULL);

  //adding pipe if need
  int pipefd[2];
  if(!with_files)
  {
      pipe(pipefd);
  }
  else
  {
      fopen("numbers.txt","w");
  }

  for (int i = 0; i < pnum; i++) {
    pid_t child_pid = fork();
    if (child_pid >= 0) {
      // successful fork
      active_child_processes += 1;
      if (child_pid == 0) {
        // child process
        // parallel somehow
        struct MinMax minmax = GetMinMax(array, array_size/pnum*i, array_size/pnum*(i+1));

        if (with_files) {
          // use files here
            FILE *fp;
            if((fp = fopen("numbers.txt","a+")) != NULL)
            {
                fprintf(fp, "%d\n%d\n", minmax.min, minmax.max);
            }
            else {
                printf("Can't open file\n");
                return 1;
            }
            fclose(fp);

        } else {

          // use pipe here
            close(pipefd[0]);
            write(pipefd[1], &minmax.min, 16);
            write(pipefd[1], &minmax.max, 16);
            close(pipefd[1]);
        }
        return 0;
      }

    } else {
      printf("Fork failed!\n");
      return 1;
    }
  }

  while (active_child_processes > 0) {
    // your code here
    int st = 0;
    wait(&st);

    active_child_processes -= 1;
  }

  struct MinMax min_max;
  min_max.min = INT_MAX;
  min_max.max = INT_MIN;

  for (int i = 0; i < pnum; i++) {
    int min = INT_MAX;
    int max = INT_MIN;

    if (with_files) {
      // read from files
        FILE *fp;
        int a = -1;
        if((fp = fopen("numbers.txt","r")) != NULL)
        {
            for(int k = 0; k < pnum; k++)
            {
            fscanf(fp, "%d\n", &a);
            if (a < min_max.min) min_max.min = a;
            fscanf(fp, "%d\n", &a);
            if (a > max) max = a;
            }
            fclose(fp);
        }
        else
        {
            printf("Can't open file\n");
            return 1;
        }

    } else {
      // read from pipes
        int a;
        close(pipefd[1]);
        while (read(pipefd[0], &a, 16) > 0)
        {
            if (a < min) min = a;
            if (a > max) max = a;
        }
        close(pipefd[0]);
    }

    if (min < min_max.min) min_max.min = min;
    if (max > min_max.max) min_max.max = max;
  }

  struct timeval finish_time;
  gettimeofday(&finish_time, NULL);

  double elapsed_time = (finish_time.tv_sec - start_time.tv_sec) * 1000.0;
  elapsed_time += (finish_time.tv_usec - start_time.tv_usec) / 1000.0;

  free(array);

  printf("Min: %d\n", min_max.min);
  printf("Max: %d\n", min_max.max);
  printf("Elapsed time: %fms\n", elapsed_time);
  fflush(NULL);
  return 0;
}