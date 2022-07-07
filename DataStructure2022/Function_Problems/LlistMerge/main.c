#include <stdio.h>
#include <stdlib.h>

typedef int ElementType;
typedef struct Node *PtrToNode;
struct Node {
  ElementType Data;
  PtrToNode Next;
};
typedef PtrToNode List;

List Read();        /* 细节在此不表 */
void Print(List L); /* 细节在此不表；空链表将输出NULL */

List Merge(List L1, List L2);

int main() {
  List L1, L2, L;
  L1 = Read();
  L2 = Read();
  L = Merge(L1, L2);
  Print(L);
  Print(L1);
  Print(L2);
  return 0;
}

/* 你的代码将被嵌在这里 */
List Merge(List L1, List L2) {
  List L = (List)malloc(sizeof(struct Node));
  List P = L;
  List P1 = L1->Next;
  List P2 = L2->Next;
  while (P1 && P2) {
    if (P1->Data <= P2->Data) {
      P->Next = P1;
      P1 = P1->Next;
    } else {
      P->Next = P2;
      P2 = P2->Next;
    }
    P = P->Next;
  }
  //如果还有剩余的元素，则将剩余的元素拼接到链表中
  if (P1) {
    P->Next = P1;
  } else {
    P->Next = P2;
  }
  // todo: free it
  L1->Next = NULL;
  L2->Next = NULL;
  return L;
}