#include <unistd.h>

int main(void)
{
        execl("test", NULL);
        return 0;
}
