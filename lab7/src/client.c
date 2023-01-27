#include <arpa/inet.h>
#include <getopt.h>
#include <netinet/in.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

#define SADDR struct sockaddr
#define SIZE sizeof(struct sockaddr_in)

int main(int argc, char *argv[]) {
  int fd;
  int nread;
  int num = atoi(argv[3]);
  int size = 0;
  struct sockaddr_in servaddr;

  if (argc < 4) {
    printf("Too few arguments \n");
    printf("usage %s ip port num\n", argv[0]);
    exit(1);
  }

  if ((fd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
    perror("socket creating");
    exit(1);
  }

  memset(&servaddr, 0, SIZE);
  servaddr.sin_family = AF_INET;
  if (inet_pton(AF_INET, argv[1], &servaddr.sin_addr) <= 0) {
    perror("bad address");
    exit(1);
  }

  servaddr.sin_port = htons(atoi(argv[2]));

  if (connect(fd, (SADDR *)&servaddr, SIZE) < 0) {
    perror("connect");
    exit(1);
  }
  if (write(fd, &num, sizeof(int)) < 0) {
    perror("write");
    exit(1);
  }
  int response = 0;
  if (read(fd, &response, sizeof(int)) < 0) {
    fprintf(stderr, "Recieve failed\n");
    exit(1);
  }
  

  //udp
  int SERV_PORT = 49001;
  int sockfd, n;
  struct sockaddr_in servaddr1;
  struct sockaddr_in cliaddr;

  memset(&servaddr1, 0, sizeof(servaddr1));
  servaddr1.sin_family = AF_INET;
  servaddr1.sin_port = htons(SERV_PORT);

  if (inet_pton(AF_INET, argv[1], &servaddr1.sin_addr) < 0) {
    perror("inet_pton problem");
    exit(1);
  }
  if ((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
    perror("socket problem");
    exit(1);
  }

  for (int i = 1; i < num + 1; i++) {
    if (sendto(sockfd, &i, sizeof(i), 0, (struct sockaddr *)&servaddr1,
               sizeof(servaddr1)) == -1) {
      perror("sendto problem1");
      exit(1);
    }
  }
  int i = 0;
  if (sendto(sockfd, &i, sizeof(i), 0, (SADDR *)&servaddr1,
             sizeof(servaddr1)) == -1) {
    perror("sendto problem2");
    exit(1);
  }
  sleep(1);
  

    response = -1;
    int ad = 0;

    while (true) {
      if (read(fd, &response, sizeof(response)) < 0) {
        fprintf(stderr, "Recieve failed\n");
        exit(1);
      }
      if(response == -1) break;
      if (sendto(sockfd, &response, sizeof(response), 0, (SADDR *)&servaddr1,
                 sizeof(servaddr1)) == -1) {
        perror("sendto problem3");
        exit(1);
      }
    }

  close(sockfd);
  close(fd);
  exit(0);
}