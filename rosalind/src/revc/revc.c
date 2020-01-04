#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#define MAX_LEN 1000

char *bin_name;

void usage_and_die()
{
  printf("usage: %s [FILENAME]\n", bin_name);
  exit(1);
}

void swap_str(char *s, size_t len)
{
  char tmp;
  for (int i = 0; i < len / 2; i++) {
    tmp = s[i];
    s[i] = s[len - 1 - i];
    s[len - 1 - i] = tmp;
  }
}

void sol(FILE *fp)
{
  char dna[MAX_LEN] = {'\0'};
  int c, i = 0;
  while ((c = fgetc(fp)) != EOF) {
    switch (c) {
      case 'A':
        c = 'T';
        break;
      case 'T':
        c = 'A';
        break;
      case 'C':
        c = 'G';
        break;
      case 'G':
        c = 'C';
        break;
    }
    dna[i++] = c;
  }
  swap_str(dna, i - 1); 
  printf("%s", dna);
}

int main(int argc, char **argv)
{
  bin_name = argv[0];
  if (argc != 2) {
    usage_and_die();
  }
  FILE *fp = fopen(argv[1], "r");
  sol(fp);
  fclose(fp);
  return 0;
}
