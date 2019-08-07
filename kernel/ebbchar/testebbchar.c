/**
* @file         testebbchar.c
* @author       Derek Molloy
* @date         7 April 2015
* @version      0.1
* @brief A linux user space program that communicates with the ebbchar.c LKM. It passes
* a string to the LKM and reads the response from the LKM. For this example to work the device
* must be called /dev/ebbchar.
* @see http://www.derekmolloy.ie/ for a full description and follow-up descriptions.
*/

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <fcntl.h>
#include <string.h>
#include <unistd.h>

#define BUFFER_LENGTH 256
static char receive[BUFFER_LENGTH];

int main(void)
{
        int ret, fd;
        char to_send[BUFFER_LENGTH];
        printf("Starting device test code example...\n");
        fd = open("/dev/ebbchar", O_RDWR);
        if (fd < 0) {
                perror("Failed to open the device...");
                return errno;
        }

        printf("Type in a short string to send to the kernel module:\n");
        scanf("%[^\n]%*c", to_send);
        printf("Writing message to the device [%s].\n", to_send);
        ret = write(fd, to_send, strlen(to_send));
        if (ret < 0) {
                perror("Failed to open the device...");
                return errno;
        }
        printf("Type in a short string to send to the kernel module:\n");
        scanf("%[^\n]%*c", to_send);
        printf("Writing message to the device [%s].\n", to_send);
        ret = write(fd, to_send, strlen(to_send));
        if (ret < 0) {
                perror("Failed to write the message to the device...");
                return errno;
        }

        printf("Press ENTER to read back from the device...\n");
        getchar();

        printf("Reading from the device...\n");
        getchar();

        printf("Reading from the device...\n");
        ret = read(fd, receive, BUFFER_LENGTH);
        if (ret < 0) {
                perror("Failed to read the message from the device.");
                return errno;
        }
        printf("The received message is: [%s]\n", receive);
        printf("End of the program\n");
        return 0;
}
