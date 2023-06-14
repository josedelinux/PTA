#include <stdio.h>
#include <stdlib.h>

#define MAXN 1001
#define MAXH -10001

int H[MAXN], size;

void Create() {
  size = 0;
  H[0] = MAXH;
}

void Insert(int X) {
  //插入元素
  //省略查询是否已满的代码
  int i;
  for (i = ++size; H[i / 2] > X; i /= 2) {
    H[i] = H[i / 2];
  }
  H[i] = X;
}

int main() {
  int n, m, x, i, j;

  scanf("%d %d", &n, &m);
  Create();
  for (i = 0; i < n; i++) {
    scanf("%d", &x);
    Insert(x);
  }
  for (i = 0; i < m; i++) {
    scanf("%d", &j);
    printf("%d", H[j]);
    while (j > 1) {
      j /= 2;
      printf(" %d", H[j]);
    }
    putchar('\n');
  }
  return 0;
}