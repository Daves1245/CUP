#include <stdio.h>

int var;

void set_var(int val)
{
  var = val;
}

int add(int val)
{
  return var + val;
}

void __attribute__ ((constructor)) init_lib(void)
{
  printf("Library has been initialized\n");
  var = 0;
}

void __attribute__ ((destructor)) clean_lib(void)
{
  printf("Library is being exited\n");
}
