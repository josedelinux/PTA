#include <stdio.h>

#define MAX_N (200000 + 7)
#define MAX(a, b) ((a) > (b) ? (a) : (b))

/*
在线处理，即时处理
*/

int n, a[MAX_N];
int ThisSum, rightidx, MaxSum, MaxCnt;
int cnt = 0;

int maxNegative = -114514;

int realTimeProcess(int A[], int N) {
  ThisSum = MaxSum = 0;
  for (int i = 0; i < N; i++) {
    if (A[i] <= 0) maxNegative = MAX(maxNegative, A[i]);  //考虑全是负数的情况
    ThisSum += A[i];                                      //向右累加
    cnt++;

    if (ThisSum > MaxSum) {
      //发现更大和则更新当前结果
      MaxSum = ThisSum;
      MaxCnt = cnt;
      rightidx = i;          //更新右边界
    } else if (ThisSum < 0)  //如果当前和小于0，则清零
      ThisSum = cnt = 0;
  }
  return MaxSum;
}

int main() {
  scanf("%d", &n);
  for (int i = 0; i < n; i++) {
    scanf("%d", &a[i]);
  }
  int result;
  if ((result = realTimeProcess(a, n)) != 0) {
    printf("%d %d %d\n", result, a[rightidx - MaxCnt + 1], a[rightidx]);
  } else if (maxNegative == 0) {
    // 0 and negative number
    printf("%d %d %d\n", 0, 0, 0);
  } else {
    // all negative
    printf("%d %d %d\n", 0, a[0], a[n - 1]);
  }
  return 0;
}
