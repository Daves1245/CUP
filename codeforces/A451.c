#include <stdio.h>

int min(int a, int b)
{
        return a < b ? a : b;
}

int main(void)
{
        int n, m, mi;
        scanf("%d %d", &n, &m);
        mi = min(n, m);
        if (mi % 2 == 0) {
                printf("Malvika");
        } else {
                printf("Akshat");
        }
        return 0;
}
