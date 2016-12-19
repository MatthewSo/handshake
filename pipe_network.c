#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#define WKP "What's red and bad for your teeth? A brick!"
#define WKP2 "What's brown and sticky? A stick!!"


int server_handshake(int * to_server){
//Step 1
  mkfifo(WKP, 0644);
  int in_fd = 0;
  printf("Server waiting for pipe\n");
  //Step 2
  *to_server = open(WKP, O_RDONLY);
  //Step 6
  char recs[MESSAGE_BUFFER_SIZE];
  read(*to_server, recs, MESSAGE_BUFFER_SIZE);
  printf("Server recieved a pipe: %s\n", recs);
  remove(WKP);
  //Step 7
  int to_client = open(recs, O_WRONLY);
  char * sendback = (char *) malloc(sizeof(char));
  sprintf(sendback, "%d", getpid());
  printf("Server sending a pipe: %s\n", sendback);
  write(to_client , sendback, strlen(sendback));
  //Step 9
  read(*to_server, recs, MESSAGE_BUFFER_SIZE);
  printf("Server recieved: %s\n", recs);
  return to_client;
}

int client_handshake(int * from_client) {
  //Step 3
  char * send = (char *) malloc(sizeof(char));
  sprintf(send, "%d", getpid());
  printf("Client sending a pipe: %s\n", send);
  mkfifo(send, 0644);
  //Step 4
  * from_client = open(WKP, O_WRONLY);
  int in_fd = 0;

  write(* from_client, send, sizeof(send));
  printf("Client waiting for pipe\n");

  //Step 5
  int to_server = open(send, O_RDONLY);
  char recc[MESSAGE_BUFFER_SIZE];
  //Step 8
  read(to_server, recc, MESSAGE_BUFFER_SIZE);
  printf("Client recieved pipe: %s\n", recc);
  remove(send);
  //Step 9
  write(*from_client, "Connected", sizeof("Connected"));
  return to_server;
}
