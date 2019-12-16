#include <stdio.h>
#include <stdlib.h> // for exit() function

#define MAX_LEN 1000

char *bin_name;

void usage_and_die()
{
  printf("usage: %s [FILENAME]\n", bin_name);
  exit(1);
}

void sol(FILE *fp)
{
   char dna[MAX_LEN] = {0}; 
   int c, i = 0;
   while ((c = fgetc(fp)) != EOF) {
    if (c == 'T') {
      c = 'U';
    }
    dna[i++] = c;
   }
   printf("%s", dna);
}

int main(int argc, char **argv)
{
  bin_name = argv[0]; 
  if (argc != 2) { usage_and_die(); }
  FILE *fp = fopen(argv[1], "r");
  sol(fp);
  fclose(fp);
  return 0;
}
