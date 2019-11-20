#include <stdio.h>
#include <limits.h>

const int N = 1e5; // limit for array size
int n; // array size
int t[2 * N];

// build the segment tree 
void build() { 
  for (int i = n - 1; i > 0; --i) {
    t[i] = t[ i * 2 ] + t[ i * 2 | 1];
  }
}

// update an element of the array
void update(int p, int value) { 
  for (t[p += n] = value; p > 1; p >>= 1) {
    t[p / 2] = t[p] + t[p^1];
  }
}

// sum on interval [l, r)
int query(int l, int r) { 
  int res = 0;
  for (l += n, r += n; l < r; l >>= 1, r >>= 1) {
    if (l & 1) res += t[l++];
    if (r & 1) res += t[--r];
  }
  return res;
}

int main() {
  scanf("%d", &n);
  for (int i = 0; i < n; ++i) scanf("%d", t + n + i);
  build();
  for (int i = 0; i < 2 * n; i++) {
    printf("%d ", t[i]);
  }
  return 0;
}
