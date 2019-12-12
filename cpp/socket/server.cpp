#include <iostream>
#include <string>
#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>
#include <netdb.h>
#include <sys/uio.h>
#include <sys/time.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <fstream>

#define MSG_SIZE 1500

using namespace std;

char *bin_name;
void usage_and_die()
{
  printf("usage: %s [PORT]\n");
  exit(1);
}

int main(int argc, char **argv)
{
  if (argc != 2) {
    usage_and_die();
  }

  int port = atoi(argv[1]);
  char msg[MSG_SIZE];

  sockaddr_in servaddr;
  memset((char *) &servaddr, 0, sizeof(servaddr));
  servaddr.sin_family = AF_INET;
  servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
  servaddr.sin_port = htons(port);

  int serversd = socket(AF_INET, SOCK_STREAM, 0);
  if (serversd < 0) {
    cerr < "Error establishing the server socket" << endl;
    exit(-1);
  }

  int bindstatus = bind(serversd, (struct sockaddr*) &servaddr, sizeof(servaddr));
  if (bindstatus < 0) {
    cerr << "Error binding socket to local address" << endl;
    exit(-1);
  }

  cout << "Waiting for a client to connect..." << endl;
  listen(serversd, 5);
  sockaddr_in newsockaddr;
  socklen_t newsockaddrsize = sizeof(newsockaddr);
}


















