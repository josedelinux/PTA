#include <stdio.h>
#include <stdlib.h>

struct PolyNode {
  int coef;               // 系数
  int expon;              // 指数
  struct PolyNode *link;  // 指向下一个节点的指针
};
typedef struct PolyNode *Polynomial;

Polynomial ReadPoly();
void PrintPoly(Polynomial P);

void Attach(int c, int e, Polynomial *pRear);
Polynomial PolyAdd(Polynomial P1, Polynomial P2);
Polynomial PolyMult(Polynomial P1, Polynomial P2);
int Compare(int arg1, int arg2);

Polynomial ReadPoly() {
  Polynomial P, Rear, t;
  int c, e, N;

  scanf("%d", &N);
  P = (Polynomial)malloc(sizeof(struct PolyNode));  //链表头空节点
  P->link = NULL;
  Rear = P;
  while (N--) {
    scanf("%d %d", &c, &e);
    Attach(c, e, &Rear); /*将当前项插入多项式尾部*/
  }
  t = P;
  P = P->link;
  free(t); /*删除临时产生的头结点*/

  return P;
}

/*输出多项式*/
void PrintPoly(Polynomial P) {
  int flag = 0; /*辅助调整输出格式用*/
  if (!P) {
    printf("0 0\n");
    return;
  }

  while (P) {
    if (!flag)
      flag = 1;
    else
      printf(" ");
    printf("%d %d", P->coef, P->expon);
    P = P->link;
  }
  printf("\n");
}

Polynomial PolyMult(Polynomial P1, Polynomial P2) {
  Polynomial P, Rear, t, t1, t2;
  int c, e;

  if (!P1 || !P2) return NULL;
  t1 = P1;
  t2 = P2;
  P = (Polynomial)malloc(sizeof(struct PolyNode));
  P->link = NULL;
  Rear = P;
  while (t2) {
    /*先用P1的第1项乘以P2,得到P*/
    Attach(t1->coef * t2->coef, t1->expon + t2->expon, &Rear);
    t2 = t2->link;
  }
  t1 = t1->link;

  while (t1) {
    t2 = P2;
    Rear = P;
    while (t2) {
      e = t1->expon + t2->expon;
      c = t1->coef * t2->coef;
      //按照降序插入,往后找
      while (Rear->link && Rear->link->expon > e) Rear = Rear->link;
      if (Rear->link && Rear->link->expon == e) {
        if (Rear->link->coef + c) {
          //不为零
          Rear->link->coef += c;
        } else {
          //为零则删去
          t = Rear->link;
          Rear->link = t->link;
          free(t);
        }
      } else {
        t = (Polynomial)malloc(sizeof(struct PolyNode));
        t->coef = c;
        t->expon = e;
        t->link = Rear->link;
        Rear->link = t;
        Rear = Rear->link;
      }
      t2 = t2->link;
    }
    t1 = t1->link;
  }
  /*删除多项式头结点*/
  t2 = P;
  P = P->link;
  free(t2);

  return P;
}

Polynomial PolyAdd(Polynomial P1, Polynomial P2) {
  int sum;
  Polynomial front, rear, temp;
  rear = (Polynomial)malloc(sizeof(struct PolyNode));
  front = rear;    /* 由front 记录结果多项式链表头结点 */
  while (P1 && P2) /* 当两个多项式都有非零项待处理时 */
    switch (Compare(P1->expon, P2->expon)) {
      case 1:
        /*P1中的数据项指数较大*/
        Attach(P1->coef, P1->expon, &rear);
        P1 = P1->link;
        break;
      case -1:
        /*P2中的数据项指数较大*/
        Attach(P2->coef, P2->expon, &rear);
        P2 = P2->link;
        break;
      case 0:
        /*两数据项指数相等*/
        sum = P1->coef + P2->coef;
        //注意判断系数和是否为0
        if (sum) Attach(sum, P1->expon, &rear);
        P1 = P1->link;
        P2 = P2->link;
        break;
    }
  /* 将未处理完的另一个多项式的所有节点依次复制到结果多项式中去 */
  for (; P1; P1 = P1->link) Attach(P1->coef, P1->expon, &rear);
  for (; P2; P2 = P2->link) Attach(P2->coef, P2->expon, &rear);
  rear->link = NULL;
  temp = front;
  front = front->link; /*令front指向结果多项式第一个非零项 */
  free(temp);          /* 释放临时空表头结点 */
  return front;
}

void Attach(int c, int e, Polynomial *pRear) {
  /* 由于在本函数中需要改变当前结果表达式尾项指针的值, */
  /* 所以函数传递进来的是结点指针的地址,*pRear指向尾项*/
  Polynomial P;

  P = (Polynomial)malloc(sizeof(struct PolyNode)); /* 申请新结点 */
  P->coef = c;                                     /* 对新结点赋值 */
  P->expon = e;
  P->link = NULL;
  /* 将P指向的新结点插入到当前结果表达式尾项的后面 */
  (*pRear)->link = P;
  *pRear = P; /* 修改pRear值 */
}

int Compare(int arg1, int arg2) {
  if (arg1 < arg2) return -1;
  if (arg1 > arg2) return 1;
  return 0;
}

int main() {
  Polynomial P1, P2;
  Polynomial PP, PS;  // product and sum

  P1 = ReadPoly();
  P2 = ReadPoly();

  PP = PolyMult(P1, P2);
  PrintPoly(PP);

  PS = PolyAdd(P1, P2);
  PrintPoly(PS);

  return 0;
}