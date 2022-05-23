#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#define MAXN 1005

const unsigned int maxnum = -1;  // for modulo
int N;

int A[MAXN];

int T[MAXN];  // result array

int fast_power(int a, int k, int q) {
  int ans = 1;
  while (k) {
    if (k & 1) ans = ans * a % (unsigned)q;
    k = k >> 1;
    a = a * a % (unsigned)q;
  }
  return ans;
}

/*计算出n个结点的树其左子树有多少给结点
formula: 2^Height -1 + X = N */
int GetLeftLength(int n) {
  int Height, X, L;
  Height = (int)floor(log2(n + 1));  // X can be ommited
  X = n + 1 - fast_power(2, Height, maxnum);
  if (X > fast_power(2, Height - 1, maxnum))
    X = fast_power(2, Height - 1, maxnum);
  L = fast_power(2, Height - 1, maxnum) - 1 + X;
  return L;
}

//从A段中选出正确的数字,填到T[TRoot]中去
void solve(int ALeft, int ARight, int TRoot) {
  int n, L;
  int LeftTRoot, RightTRoot;
  n = ARight - ALeft + 1;
  if (n == 0) return;
  L = GetLeftLength(n);
  T[TRoot] = A[ALeft + L];
  LeftTRoot = TRoot * 2 + 1;
  RightTRoot = LeftTRoot + 1;
  solve(ALeft, ALeft + L - 1, LeftTRoot);
  solve(ALeft + L + 1, ARight, RightTRoot);
}
int compare(const void* a, const void* b) {
  int arg1 = *(const int*)a;
  int arg2 = *(const int*)b;

  if (arg1 < arg2) return -1;
  if (arg1 > arg2) return 1;
  return 0;
}

int main() {
  scanf("%d", &N);
  for (int i = 0; i < N; i++) scanf("%d", &A[i]);

  // get'em sorted
  qsort(A, N, sizeof(int), compare);

  solve(0, N - 1, 0);

  for (int i = 0; i < N; i++) {
    if (i == 0)
      printf("%d", T[i]);
    else
      printf(" %d", T[i]);
  }
  return 0;
}