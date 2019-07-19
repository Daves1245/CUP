#include <stdio.h>

void sol(int n, int f)
{
        printf("I %s %s ", f ? "love" : "hate", n == 1 ? "it" : "that");
        if (n != 1) sol(n - 1, !f);
}
int main(void)
{
        int n;
        scanf("%d", &n);
        sol(n, 0);
        return 0;
}
