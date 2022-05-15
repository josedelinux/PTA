/*
final Solution
*/
#include <stdio.h>

/*
path compression solution
https://en.wikipedia.org/wiki/Ackermann_function
*/
#define MaxSize 10005

typedef int ElementType; /*默认元素可以用非负整数表示*/
typedef int SetName;     /*默认用根节点的下标作文集合名称*/
typedef ElementType SetType[MaxSize];

int Find(SetType S, ElementType X) {
  /*默认集合元素全部初始化为-1*/
  if (S[X] < 0)
    return X;
  else
    return S[X] = Find(S, S[X]);
}

void Union(SetType S, SetName Root1, SetName Root2) {
  /* 按秩归并 */
  if (S[Root2] < S[Root1]) /* Height: Root2 > Root1 */
    S[Root1] = Root2;
  else {
    if (S[Root2] == S[Root1]) S[Root1]--;
    S[Root2] = Root1;
  }
}

void Initialization(SetType S, int n) {
  /*默认集合元素全部初始化为-1*/
  for (int i = 0; i < n; i++) S[i] = -1;
}

void Input_connection(SetType S) {
  ElementType u, v;
  SetName Root1, Root2;
  scanf("%d %d\n", &u, &v);
  Root1 = Find(S, u - 1);
  Root2 = Find(S, v - 1);
  if (Root1 != Root2) Union(S, Root1, Root2);
}

void Check_network(SetType S, int n) {
  int i, counter = 0;
  for (i = 0; i < n; i++) {
    if (S[i] < 0) counter++;
  }
  if (counter == 1)
    printf("The network is connected.\n");
  else
    printf("There are %d components.\n", counter);
}

void Check_connection(SetType S) {
  ElementType u, v;
  SetName Root1, Root2;
  scanf("%d %d\n", &u, &v);
  Root1 = Find(S, u - 1);
  Root2 = Find(S, v - 1);
  if (Root1 == Root2)
    printf("yes\n");
  else
    printf("no\n");
}

int main() {
  SetType S;
  int n;
  char in;
  scanf(" %d\n", &n);
  Initialization(S, n);
  do {
    scanf("%c", &in);
    switch (in) {
      case 'I':
        Input_connection(S);
        break;
      case 'C':
        Check_connection(S);
        break;
      case 'S':
        Check_network(S, n);
        break;
    }
  } while (in != 'S');
  return 0;
}
