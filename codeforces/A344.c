#include <stdio.h>

int main(void) {
        int n;
        scanf("%d", &n);
        getchar();
        
        int sum = 1;
        getchar();
        for (int i = 1; i < n; i++) {
                int cur = getchar();
                getchar();
                int next = getchar();
                if (cur == next) {
                        sum++;
                }
        }
        
        printf("%d", sum);
        return 0;
}
