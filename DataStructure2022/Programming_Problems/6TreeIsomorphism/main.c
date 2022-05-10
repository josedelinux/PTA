#include <stdio.h>

#define MaxTree 10
#define ElementType char
#define Tree int
#define nil -1

struct TreeNode {
  ElementType Element;
  Tree Left;
  Tree Right;
} T1[MaxTree], T2[MaxTree];

Tree BuildTree(struct TreeNode T[]) {
  int N;
  char cl, cr;
  int check[MaxTree];
  Tree Root = nil;
  scanf("%d\n", &N);
  if (N) {
    for (int i = 0; i < N; i++) check[i] = 0;

    for (int i = 0; i < N; i++) {
      scanf("%c %c %c\n", &T[i].Element, &cl, &cr);
      if (cl != '-') {
        T[i].Left = cl - '0';
        check[T[i].Left] = 1;
      } else
        T[i].Left = nil;
      if (cr != '-') {
        T[i].Right = cr - '0';
        check[T[i].Right] = 1;
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

int Isomorphic(Tree R1, Tree R2) {
  if (R1 == nil && R2 == nil) return 1;           /*both empty*/
  if (R1 == nil || R2 == nil) return 0;           /*one empty*/
  if (T1[R1].Element != T2[R2].Element) return 0; /*root are different*/
  if ((T1[R1].Left == nil) && (T2[R2].Left == nil))
    return Isomorphic(T1[R1].Right, T2[R2].Right); /*both have no left subtree*/
  if (((T1[R1].Left != nil) && (T2[R2].Left != nil)) &&
      ((T1[T1[R1].Left].Element) == (T2[T2[R2].Left].Element)))
    /*no need to swap the left and the right*/
    return (Isomorphic(T1[R1].Left, T2[R2].Left) &&
            Isomorphic(T1[R1].Right, T2[R2].Right));

  else /*need to swap the left and the right*/
    return (Isomorphic(T1[R1].Right, T2[R2].Left) &&
            Isomorphic(T1[R1].Left, T2[R2].Right));
}

int main() {
  Tree R1, R2;
  R1 = BuildTree(T1);
  R2 = BuildTree(T2);
  if (Isomorphic(R1, R2))
    printf("Yes\n");
  else
    printf("No\n");

  return 0;
}