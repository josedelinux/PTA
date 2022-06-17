#include <stdio.h>
#define MAX(a, b) ((a > b) ? (a) : (b))

#define MAX_N (100000 + 7)

int n, a[MAX_N];

int rtp(int A[], int N);

int main() {
  scanf("%d", &n);
  for (int i = 0; i < n; i++) {
    scanf("%d", &a[i]);
  }
  printf("%d\n", rtp(a, n));
  return 0;
}

/*
在线处理，即时处理
*/
int rtp(int A[], int N) {
  int ThisSum, MaxSum;
  int i;
  ThisSum = MaxSum = 0;
  for (i = 0; i < N; i++) {
    ThisSum += A[i];       //向右累加
    if (ThisSum > MaxSum)  //发现更大和则更新当前结果
      MaxSum = ThisSum;
    else if (ThisSum < 0)  //如果当前和小于0，则清零
      ThisSum = 0;
  }
  return MaxSum;
}
