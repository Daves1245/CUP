#ifndef BOILERPLATE_H
#define BOILERPLATE_H

#include <stdio.h>
#include <stdlib.h>

char *bin_name;
char *usage_args;

inline void usage() {
 printf("usage: %s %s\n", bin_name, usage_options); 
}

inline void usage_and_exit() {
  usage();
  exit(1);
}

#define SET_USAGE_ARGS(args) usage_args = (args)

#endif

