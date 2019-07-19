#include <stdio.h>

int min(int a, int b) {
        return a < b ? a : b;
}

int max(int a, int b) {
        return a > b ? a : b;
}

int main(void)
{
        int n;
        scanf("%d", &n);
        int arr[n];

        int min = 101, min_index;
        int max = 0, max_index;
        for (int i = 0; i < n; i++) {
                int c; 
                scanf("%d", &c);

                if (c <= min) {
                        min_index = i;
                        min = c;
                }

                if (c > max) {
                        max_index = i;
                        max = c;
                }
        }

        int sum = max_index + n - (min_index + 1);
        if (min_index < max_index) {
                sum--;
        }

        printf("%d", sum);
        return 0;
}
