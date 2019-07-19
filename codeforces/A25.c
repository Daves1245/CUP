#include <stdio.h>

int main(void)
{
        int n;
        scanf("%d", &n);

        int a, b, c, p;
        scanf("%d %d %d", &a, &b, &c);
        
        a %= 2;
        b %= 2;
        c %= 2;
        if (a == b && c != a) printf("3");
        if (a == c && b != a) printf("2");
        if (b == c && a != b) printf("1");
        p = a;

        for (int i = 4; i < n; i++) {
                int d;
                scanf("%d", &d);
                if (d % 2 != p) {
                        printf("%d", i);
                }
        }
        return 0;
}
