#include <stdio.h>

#define MAX_SIZE 110

int main(void) {
        int a[MAX_SIZE];
        for (int i = 0; i < MAX_SIZE; i++) {
                int c = getchar();
                if (c == '\n') {
                        a[i] = -1;
                        break;
                } else {
                        a[i] = c;
                }
        }

        for (int i = 0; a[i] != -1; i++) {
                if (a[i] != getchar()) {
                        printf("%d", 1);
                } else {
                        printf("%d", 0);
                }
        }

        return 0;
}
