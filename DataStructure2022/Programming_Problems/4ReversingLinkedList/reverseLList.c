/*
http://www.lounuonuo.top/archives/9.html
*/
#include <stdbool.h>
#include <stdio.h>

#define N 100000

int n, K;
int head;

typedef int Ptr;

typedef struct Node {
  int Element;
  Ptr Next;
} NODE, *PNODE;

NODE List[N];

Ptr Reverse(Ptr head, int K) {
  Ptr pNew, pOld, pTmp;
  int i = 1;

  // initial
  pNew = head;
  pOld = List[pNew].Next;

  while (i < K) {
    // Remain the old list;
    pTmp = List[pOld].Next;

    // Reverse the first old node to the new list;
    List[pOld].Next = pNew;

    // Remove pointer;
    pNew = pOld;
    pOld = pTmp;

    i++;
  }

  List[head].Next = pOld;

  return pNew;
}

bool ifReverse(Ptr head, int K) {
  if (head == -1) {
    return false;
  }

  int i = 1;

  while (List[head].Next != -1) {
    head = List[head].Next;
    i++;
    if (i == K) {
      return true;
    }
  }

  return false;
}

Ptr reverseAll(Ptr head, int K) {
  Ptr headReversedList = head, tailReversed = head;
  Ptr headEpoch;

  if (ifReverse(head, K)) {
    headReversedList = Reverse(head, K);
    headEpoch = List[tailReversed].Next;
  } else {
    return headReversedList;
  }

  while (ifReverse(headEpoch, K)) {
    List[tailReversed].Next = Reverse(headEpoch, K);
    tailReversed = headEpoch;
    headEpoch = List[tailReversed].Next;
  }

  return headReversedList;
}

int main() {
  Ptr tmpAddr;

  scanf("%d %d %d", &head, &n, &K);

  for (int i = 0; i < n; i++) {
    scanf("%d", &tmpAddr);
    scanf("%d %d", &List[tmpAddr].Element, &List[tmpAddr].Next);
  }

  head = reverseAll(head, K);

  while (List[head].Next != -1) {
    printf("%05d %d %05d\n", head, List[head].Element, List[head].Next);
    head = List[head].Next;
  }

  printf("%05d %d %d\n", head, List[head].Element, List[head].Next);

  return 0;
}
