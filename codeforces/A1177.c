#include <stdio.h>
#include <math.h>

int digits(int a)
{
        int ret = 0;
        while (a > 0) {
                ret++;
                a /= 10;
        }
        return ret;
}

int len(int x)
{
        int d = digits(x);
        int td = (int) pow(10, d);
        return td - 1 + (d) * (x - td + 1);
}

int main(void)
{
        for (int i = 1; i <= 101; i++) {
                printf("%d %d\n", i, len(i));
        }
        return 0;
}
