#include <sys/wait.h> /* for waitpid() */
int main(int argc, char *argv[]) {
        int servSock; /* Socket descriptor for server */
        int clntSock; /* Socket descriptor for client */
        unsigned short echoServPort; /* Server port */
        pid_t processID; /* Process ID from fork()*/
        unsigned int childProcCount = 0; /* Number of child processes */
        if (argc != 2) { /* Test for correct number of arguments */
                        fprintf(stderr, "Usage: %s <Server Port>\n", argv[0]);
                        exit(1);
                       }
        echoServPort = atoi(argv[1]); /* First arg: local port */
        servSock = CreateTCPServerSocket(echoServPort);
        for (;;) { /* Run forever */
                  clntSock = AcceptTCPConnection(servSock);
                  if ((processID = fork()) < 0) DieWithError (“fork() failed”); /* Fork child process */
                  else if (processID = 0) { /* This is the child process */
                                           close(servSock); /* child closes listening socket */
                                           HandleTCPClient(clntSock);
                                           exit(0); /* child process terminates */
                                          }
                  close(clntSock); /* parent closes child socket */
                  childProcCount++; /* Increment number of outstanding child processes */
                  while (childProcCount) { /* Clean up all zombies */
                                          processID = waitpid((pid_t) -1, NULL, WHOANG); /* Non-blocking wait */
                                          if (processID < 0) DieWithError (“...”);
                                          else if (processID == 0) break; /* No zombie to wait */
                                          else childProcCount--; /* Cleaned up after a child */
                                         }
                 }
        /* NOT REACHED */
}
