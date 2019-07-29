#include <stdio.h>
#include <stdlib.h>

#define MESSAGE_MAX_SIZE 50

/* These methods allocate memory
* on the heap and MUST BE FREED
* BEFORE A PROGRAM CLOSES!!
*/
// Grab the next word from stdin
char * input_next();
// Grab the next line from stdin
char * input_nextln();

