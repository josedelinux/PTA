/*

// //original one
// Ptr Reverse(Ptr head, int K) {
//   Ptr new, old, tmp;
//   int cnt = 1;
//   new = head->next;
//   old = new->next;
//   while (cnt < K) {
//     tmp = old->next;
//     old->next = new;
//     new = old;
//     old = tmp;
//     cnt++;
//   }
//   head->next->next = old;
//   return new;
// }


*/
#define DEBUGn

#include <stdio.h>
#include <stdlib.h>
#define MaxSize 100005
#define nil -1

typedef int Ptr;

// FirstAddr: address of the first node
// N: total number of nodes
// K: the length of the sublist to be reversed
int FirstAddr, N, K;

// use list[address] to access a array element
struct Lnode {
  int data;
  Ptr naddr;
} list[MaxSize];

Ptr Reverse(Ptr head, int K) {
  Ptr new, old, tmp;
  int cnt = 1;
  new = list[head].naddr;
  old = list[new].naddr;
  while (cnt < K) {
    tmp = list[old].naddr;  // tmp = old->next
    list[old].naddr = new;  // old->next = new; //reverse it

    // move forward
    new = old;
    old = tmp;

    cnt++;
  }
  list[list[head].naddr].naddr = old;  // head->next->next = old;
  return new;                          // this is the new head->next
}

void DumpList() {
  printf("Addr  Data  Next\n");
  for (int i = 0; i < MaxSize; i++) {
    if (list[i].data != 0)
      printf("%05d  %d  %05d\n", i, list[i].data, list[i].naddr);
  }
  printf("DumpList() exit\n");
}

void BuildList() {
  Ptr tmpAddr;
  for (int i = 0; i < N; i++) {
    scanf("%5d", &tmpAddr);
    scanf("%d %d", &list[tmpAddr].data, &list[tmpAddr].naddr);
  }
}

void Print(Ptr head) {
  // forward to valid one
  Ptr tmp = list[head].naddr;

  while (list[tmp].naddr != nil) {
    printf("%05d %d %05d\n", tmp, list[tmp].data, list[tmp].naddr);
    tmp = list[tmp].naddr;
  }
  printf("%05d %d %d\n", tmp, list[tmp].data, list[tmp].naddr);
}

// count valid linked list nodes
int cnt(Ptr head) {
  int cnt = 1;
  // forward to valid one
  Ptr tmp = list[head].naddr;

  while (list[tmp].naddr != nil) {
    cnt++;
    tmp = list[tmp].naddr;
  }
#ifdef DEBUG
  printf("cnt() == %d\n", cnt);
#endif
  return cnt;
}

int main() {
  scanf("%d %d %d", &FirstAddr, &N, &K);
  BuildList();

#ifdef DEBUG
  DumpList();
#endif

  // pick an empty node as head node
  Ptr h = MaxSize - 1;

  list[h].data = nil;
  list[h].naddr = FirstAddr;

#ifdef DEBUG
  Print(h);
#endif

  Ptr tmp = h;
  int n = cnt(h);  // real number of elements
  for (int i = 0; i < n / K; i++) {
    list[tmp].naddr = Reverse(tmp, K);
    for (int i = 0; i < K; i++) {
#ifdef DEBUG
      printf("Moving head to %5d\n", list[tmp].naddr);
#endif
      tmp = list[tmp].naddr;
    }
  }
  Print(h);

  return 0;
}
