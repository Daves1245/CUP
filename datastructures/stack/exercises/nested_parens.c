#include <stdio.h>
#include <stdlib.h>

#include "stack.h"

#define BUFF_SIZE 100

char *bin_name;

void usage_and_die()
{
  printf("usage: %s [FILENAME]\n", bin_name);
  exit(1);
}

void err(const char *err_msg)
{
  fprintf(stderr, "%s", err_msg);
}

int main(int argc, char **argv)
{
  bin_name = argv[0];
  if (argc < 2) {
    usage_and_die();
  }
  FILE *filep = fopen(argv[1], "r"); 
  if (!filep) {
    err("file not found");
    return -1;
  }

  char buffer[BUFF_SIZE];
  while(fscanf(filep, "%s", buffer) > 0) {
    printf("%s\n", buffer);
  }
}
