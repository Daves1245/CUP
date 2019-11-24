#include <stdio.h>
#include "stack.h.1"
#include <errno.h>
#include <string.h>

#define MAX_LENGTH 100

int main(void)
{
        stack * s = stack_new();
        
        stack_delete(s);
        return 0;
}

