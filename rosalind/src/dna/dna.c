#include <stdlib.h>
#include <stdio.h>

char *bin_name;

void usage_and_die()
{
  printf("usage: %s [DATASET]\n", bin_name);
  exit(1);
}

void sol(FILE *fp)
{
  int count[26] = { 0 };
  int c;
  while ((c = fgetc(fp)) != EOF) {
   count[c - 'A']++;
  }

  printf("%d %d %d %d\n", count[0], count[2], count[6], count[19]); 
}

int main(int argc, char **argv)
{
  bin_name = argv[0];
  if (argc != 2) { usage_and_die(); }
  FILE *fp = fopen(argv[1], "r");
  sol(fp);
  fclose(fp);
}
