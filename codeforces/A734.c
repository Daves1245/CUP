#include <stdio.h>

int main(void) {
        int n;
        scanf("%d", &n);
        getchar();
        int a = 0;
        int d = 0;
        for (int i = 0; i < n; i++) {
                int c = getchar();
                if (c == 'A') {
                        a++;
                } else {
                        d++;
                }
        }

        if (a > d) {
                printf("Anton");
        } else if (a < d) {
                printf("Danik");
        } else {
                printf("Friendship");
        }

        return 0;
}
