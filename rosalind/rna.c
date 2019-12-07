#include <stdio.h>

char *bin_name;

void sol(FILE *fp)
{
  
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
