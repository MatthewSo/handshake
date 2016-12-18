#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>



int server_handshake(int * to_server){



  int in_fd = 0;
printf("Server waiting for pipe\n");
  //while (!in_fd){
    in_fd = open("client-to-server", O_RDONLY);
  //}

  //char * recs = (char *) malloc(sizeof(char));
  char recs[1000];
  printf("%d\n", sizeof(recs));
  read("client-to-server", recs, sizeof(recs));
  printf("Server recieved a pipe: %s\n", recs);
  if (strcmp(recs, "recieved server-to-client") == 0) {
    printf("Server sending pipe\n");
    write("server-to-client", "recieved client-to-server", sizeof("recieved client-to-server"));
    mkfifo("server-to-client", 0644);
    open("server-to-client", O_WRONLY);
  }
  printf("Server made a mistake somewhere\n");
  return getpid();
}

int client_handshake(int * to_client) {
  //int pid = getpid();
  mkfifo("client-to-server", 0644);
  int fd = open("client-to-server", O_WRONLY);
  int in_fd = 0;
  printf("Client sending a pipe\n");
  char * send = "recieved server-to-client";
  printf("%d\n", sizeof(send));
  write("client-to-server", send, sizeof(send));
  printf("Client waiting for pipe\n");
  /*while (!in_fd){

  }*/

  in_fd = open("server-to-client", O_RDONLY);
  char * recc = (char *) malloc(sizeof(char));
  printf("Client really hopeful\n");
  read("server-to-client", recc, sizeof(recc));
  printf("Client recieved pipe\n");
  if (strcmp(recc, "recieved server-to-client") == 0) {
    write("server-to-client", "recieved client-to-server", sizeof("recieved client-to-server"));
  }
  return getpid();
}
