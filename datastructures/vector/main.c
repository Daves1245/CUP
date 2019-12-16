#include <stdio.h>

#include "vector.h"
#include "../../helpfull/io/input.c"

#define MAX_INPUT 10

int main(void)
{
  vector *v = vector_new();

  int n;
  scanf("%d", &n);
  getchar();

  for (int i = 0; i < n; i++) {
    vector_add(v, input_next());
  }

  for (int i = 0; i < vector_size(v); i++) {
    printf("%d:%s\n", i, (const char *) vector_get(v, i));
  }

  vector_remove(v, (int) vector_size(v) / 2);

  for (int i = 0; i < vector_size(v); i++) {
    printf("%d:%s\n", i, (const char *) vector_get(v, i));
  }

  while (!vector_empty(v)) {
    vector_remove(v, vector_size(v) - 1);
  }

  printf("end:\n");
  for (int i = 0; i < vector_size(v); i++) {
    printf("%s", (const char *) vector_get(v, i));
  }

  return 0;
}
