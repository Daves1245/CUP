#include <stdio.h>

#include "add.h"
#include "answer.h"

int main(void)
{
  set_var(5);
  printf("%d", add(7));
  printf("%d", answer());
  return 0;
}
