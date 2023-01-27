#ifndef UTILS_H
#define UTILS_H


struct MinMax {
  int min;
  int max;
};

//Read end of pipe for child PIDs, made for killing function
int GPipeReadEnd;
//Need it to send pnum to killing function
int Gpnum;

void GenerateArray(int *array, unsigned int array_size, unsigned int seed);
void KillYourChildren (int signo);

#endif