#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h> 
#include <sys/stats.h>


int server_handshake(int * to_server){
  
  mkfifo("sHand", 0644);
  
  int in_fd = 0;

  while (!in_fd){
    in_fd = open("cHand", O_RDONLY);}
  
}
