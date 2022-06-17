#include <stdio.h>
#define MAX(a, b) ((a > b) ? (a) : (b))

#define MAX_N (100000 + 7)

int n, a[MAX_N];

/*
divide and conquer
T(N) = 2T(N^2) + c(n)
=2[2T(N^2) + c(n)] + c(n)
=2^k O(1) + ckN
=O(NlogN)
其中N/2^k = 1
*/
int DivideConquer(int data[], int left, int right) {
  int mid;
  int leftMaxSum, rightMaxSum;
  int leftBoardSum, rightBoardSum;
  int leftMaxBoardSum, rightMaxBoardSum;
  /* 退出条件 */
  if (left == right) return data[left];

  /* “分的过程” */
  mid = (left + right) / 2;  //找到中分点

  /* 递归求两边的最大值 */
  leftMaxSum = DivideConquer(data, left, mid);        // 左边最大值
  rightMaxSum = DivideConquer(data, mid + 1, right);  // 右边最大值

  /* 跨越边界的最大值 := leftMaxBoardSum + rightMaxBoardSum  */
  leftMaxBoardSum = data[mid];
  leftBoardSum = 0;
  for (int i = mid; i >= left; i--) {
    leftBoardSum += data[i];
    if (leftBoardSum > leftMaxBoardSum) leftMaxBoardSum = leftBoardSum;
  }  //左边界扫描

  rightMaxBoardSum = data[mid + 1];
  rightBoardSum = 0;
  for (int i = mid + 1; i <= right; i++) {
    rightBoardSum += data[i];
    if (rightBoardSum > rightMaxBoardSum) rightMaxBoardSum = rightBoardSum;
  }  //有边界扫描

  /* 治的过程，最大值为左边的最大值、右边最大值，跨越边界最大值之中的最大值 */
  return MAX(MAX(leftMaxSum, rightMaxSum), leftMaxBoardSum + rightMaxBoardSum);
}

int main() {
  scanf("%d", &n);
  for (int i = 0; i < n; i++) {
    scanf("%d", &a[i]);
  }
  printf("%d\n", DivideConquer(a, 0, n - 1));
  return 0;
}
