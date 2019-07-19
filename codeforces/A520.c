#include <stdio.h>

int main(void) {
        int n;
        scanf("%d", &n);
        if (n < 26) {
                printf("NO");
                return 0;
        }

        getchar();

        register unsigned long a = 0;
        for (int i = 0; i < n; ++i) {
                int c = getchar();
                if (c > 'z') {
                        c -= 'A';
                } else {
                        c -= 'a';
                }

                a |= (1 << c);
        }

        printf("%s", (a + 1 == 67108864) ? "YES" : "NO");
        return 0;
}
