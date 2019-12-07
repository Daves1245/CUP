#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

#define BUFFER_SIZE 1

char *bin_name;

void usage_and_die()
{
  printf("usage: %s [FILENAME]\n", bin_name);
  exit(1);
}

int main(int argc, char **argv)
{
  // misc. configuration
  bin_name = argv[0];
  if (argc < 2) {
    usage_and_die();
  }

  // open file, check for errors
  int fd = open(argv[1], O_RDWR);

  // get ready to read
  ssize_t bytes_read;
  char buffer[BUFFER_SIZE];
  size_t num_bytes_to_read = 1;
  // read and print to stdout
  while ((bytes_read = read(fd, buffer, num_bytes_to_read)) > 0) {
    printf("%s", buffer);
  }
  printf("EOF\n");
}
