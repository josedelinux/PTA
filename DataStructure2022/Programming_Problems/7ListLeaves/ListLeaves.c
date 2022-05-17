#include <stdio.h>
#include <stdlib.h>

#define nil -1
#define MaxTree 10
#define Tree int

int N, check[MaxTree];
struct TreeNode {
  int Data;
  Tree Left;
  Tree Right;
} T[MaxTree], queue[MaxTree];

Tree BuildTree() {
  char cl, cr;
  int Root = -1;
  scanf("%d", &N);
  if (N) {
    for (int i = 0; i < N; i++) check[i] = 0;
    for (int i = 0; i < N; i++) {
      T[i].Data = i;
      scanf(" %c %c", &cl, &cr);
      if (cl != '-') {
        T[i].Left = cl - '0';
        check[cl - '0'] = 1;
      } else
        T[i].Left = nil;
      if (cr != '-') {
        T[i].Right = cr - '0';
        check[cr - '0'] = 1;
      } else
        T[i].Right = nil;
    }

    for (int i = 0; i < N; i++)
      if (!check[i]) {
        Root = i;
        break;
      }
  }
  return Root;
}

int first, last;

void Push(struct TreeNode TN) { queue[++last] = TN; }

struct TreeNode Pop() {
  return queue[++first];
}

void PrintLeaves(Tree R) {
  int leaves[N];
  int i, k = 0;
  struct TreeNode tmp;
  Push(T[R]);
  for (i = 0; i < N; i++) {
    tmp = Pop();
    if (tmp.Left == nil && tmp.Right == nil) leaves[k++] = tmp.Data;
    if (tmp.Left != nil) Push(T[tmp.Left]);
    if (tmp.Right != nil) Push(T[tmp.Right]);
  }
  for (i = 0; i < k - 1; i++) printf("%d ", leaves[i]);
  printf("%d\n", leaves[k - 1]);
}

int main() {
  Tree t;
  t = BuildTree();
  PrintLeaves(t);
  return 0;
}