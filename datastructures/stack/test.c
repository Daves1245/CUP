#include <stdio.h>
#include <stdlib.h>

int main(void)
{
        char *msg = malloc(sizeof(*msg) * 10);
        scanf("%s", msg);
        char *other = msg;
        msg = NULL;
        free(msg);
        printf("%s", other);
        free(other);
        return 0;
}
