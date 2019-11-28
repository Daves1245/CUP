#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define INVALID_TIME -1
#define FORK_FAILED -2

static char *bin_name;

void usage_and_exit();
int parse_time(char*, long*);

int main(int argc, char **argv)
{
    /* Config */ 
    bin_name = argv[0];
    long sleep_time;
    pid_t pid, w;
    int wstatus;

    /* Check for proper # of args  */
    if (argc != 3) {
        usage_and_exit();
    }
    /* Check the provided sleep time is valid */
    if (parse_time(argv[2], &sleep_time) != 0) {
        perror("wait time must be a positive integer");
        exit(INVALID_TIME);
    }

    #ifdef DEBUG_ON
    printf("sleep_time: %d", sleep_time);
    #endif
    
    /* Determine where we are and what we have to do */
    if ((pid = fork()) < 0) { // Error, abort
        perror("fork failed"); 
        return 0;
    } else if (pid == 0) { // Child process  
        /* XXX check if binary exists first */
        #ifdef DEBUG_ON
        printf("binary: %s", argv[1]);
        #endif
        execl(argv[1], NULL);
        exit(EXIT_SUCCESS);
    } else { // Parent process
        for (long i = 0; i < sleep_time; i++) {
            w = waitpid(pid, &wstatus, WNOHANG);	
            // XXX add signal handling
            if (WIFEXITED(w)) {
                #ifdef DEBUG_ON
                printf("subprocess terminated before timeout\n");
                #endif
                exit(EXIT_SUCCESS);
            }
            sleep(1);
        }
    }
    return 0;
}

/*
 * Print the usage banner and exit
 */
void usage_and_exit()
{
    printf("usage: %s [command] [seconds]\n", bin_name);
    exit(1);
}

/*
 * Check if second argument is a valid number
 * Store it in sleep_time while we're checking
 * XXX - add support for suffixes (s, m, h) 
 * idea: regex?
 */
int parse_time(char *argp, long *sleep_time)
{
    *sleep_time = 0;
    long offset = 1;
    for (int i = strlen(argp) - 1; i >= 0; --i) {
        int cur = argp[i] - '0';
        if (cur > 10) {
            return -1; // not a digit .:. not a valid number
        }
        *sleep_time += cur * offset;
        offset *= 10;
    }
    return 0;
}

