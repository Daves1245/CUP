#include <stdio.h>

#define MAX_SIZE 50

char *bin_name;

int memo[50] = {0};

int kfib(int n, int k)
{
  if (n < 0) { return 0; }
  if (n == 1 || n == 0) { return n; } 
  else if (memo[n] != 0) { return memo[n]; }
  else { return memo[n] = kfib(n - 1, k) + k * kfib(n - 1, k);
}

void sol(FILE *fp)
{
  int n, k;
  fscanf(fp, "%d %d", &n, &k);
  printf("%d\n", kfib(n, k)); 
}

void usage_and_die()
{
  printf("usage: %s [FILENAME]\n");
}

int main(int argc, char **argv)
{
  bin_name = argv[0]; 
  if (argc != 2) {
    usage_and_die();
  }
  FILE *fp = fopen(argv[0], "r");
  if (fp == NULL) {
    printf("file %s: not found\n", argv[1]);
    exit(1);
  }
  sol(fp);
  fclose(fp);
  return 0;
}
