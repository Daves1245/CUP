#include <stdio.h>

int main(void) {
        int l, b;
        scanf("%d %d", &l, &b);
        int c = 0;
        while (l <= b) {
                l *= 3;
                b *= 2;
                c++;
        }

        printf("%d", c);
        return 0;
}
