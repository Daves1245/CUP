#include <stdio.h>

int main(void) {
        int n, h; 
        scanf("%d %d", &n, &h);

        int over = 0;
        for (int i = 0; i < n; i++) {
                int cur;
                scanf("%d", &cur);
                if (cur > h) {
                        over++;
                }
        }

        printf("%d", n + over);
        return 0;
}
