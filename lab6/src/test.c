#include "factorial.h"
#include "pthread.h"
#include <errno.h>
#include <getopt.h>
#include <netdb.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/time.h>
struct Server {
  char ip[255];
  int port;
};

int main(int argc, char **argv) {
  double elapsed_time;
  unsigned int servers_num = 1;
  struct Server to;
  struct timeval finish_time;
   to.port = 20001;
   memcpy(to.ip, "95.72.135.152", sizeof("95.72.133.152"));
  int sck;
    struct timeval start_time;

    struct hostent *hostname = gethostbyname(to.ip);
    if (hostname == NULL) {
      fprintf(stderr, "gethostbyname failed with %s\n", to.ip);
      exit(1);
    }

    struct sockaddr_in server;
    server.sin_family = AF_INET;
    server.sin_port = htons(to.port);
    server.sin_addr.s_addr = *((unsigned long *)hostname->h_addr_list[0]);

    sck = socket(AF_INET, SOCK_STREAM, 0);
    if (sck < 0) {
      fprintf(stderr, "Socket creation failed!\n");
      exit(1);
    }
    printf("hfg\n");
    if (connect(sck, (struct sockaddr *)&server, sizeof(server)) < 0) {
      fprintf(stderr, "Connection failed\n");
      exit(1);
    }
    printf("sdsd\n");
    char task[sizeof(uint64_t)*3];
    uint64_t a = 12;
    memcpy(task, &a, sizeof(uint64_t));
    memcpy(task+sizeof(uint64_t), &a, sizeof(uint64_t));
    memcpy(task+2*sizeof(uint64_t), &a, sizeof(uint64_t));

    printf("ss\n");
    gettimeofday(&start_time, NULL);
    
    if (send(sck, task, sizeof(task), 0) < 0) {
      fprintf(stderr, "Send failed\n");
      exit(1);
    }
    printf("sended\n");
    char response[sizeof(uint64_t)];
    recv(sck, response, sizeof(response), 0);
    gettimeofday(&finish_time, NULL);

  elapsed_time = (finish_time.tv_sec - start_time.tv_sec) * 1000.0;
  elapsed_time += (finish_time.tv_usec - start_time.tv_usec) / 1000.0;

  printf("time = %f\n", elapsed_time);
  return 0;
}