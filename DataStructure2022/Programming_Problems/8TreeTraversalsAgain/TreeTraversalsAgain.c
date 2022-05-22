#include <stdio.h>
#include <string.h>
#define MAXN 30

int pre[MAXN], in[MAXN], post[MAXN];

int N;

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#define ERROR 0

typedef int ElementType;
typedef int Position;

struct SNode {
  ElementType* Data; /* 存储元素的数组 */
  Position Top;      /* 栈顶指针 */
  int MaxSize;       /* 堆栈最大容量 */
};

typedef struct SNode* Stack;

Stack CreateStack(int MaxSize) {
  Stack S = (Stack)malloc(sizeof(struct SNode));
  S->Data = (ElementType*)malloc(MaxSize * sizeof(ElementType));
  S->Top = -1;
  S->MaxSize = MaxSize;
  return S;
}

bool IsFull(Stack S) { return S->Top == S->MaxSize - 1; }

bool Push(Stack S, ElementType X) {
  if (IsFull(S)) {
    printf("Stack is full\n");
    return false;
  } else {
    S->Data[++(S->Top)] = X;
    return true;
  }
}

bool IsEmpty(Stack S) { return S->Top == -1; }

ElementType Pop(Stack S) {
  if (IsEmpty(S)) {
    printf("Stack is empty\n");
    return ERROR; /* ERROR是ElementType的特殊值，标志错误 */
  } else
    return (S->Data[(S->Top)--]);
}

//根据post数组输出结果
void PrintResult(int n) {
  int i;
  for (i = 0; i < n; i++) {
    if (i == 0)
      printf("%d", post[i]);
    else
      printf(" %d", post[i]);
  }
  printf("\n");
}

//解题函数
//构造post序列
// preL为pre数组起始下标
// inL为in数组起始下标
// postL为post数组起始下标
// n为总节点个数
void Solve(int preL, int inL, int postL, int n) {
  // root为根结点数据，L为左子树节点个数，R为右子树节点个数
  int root, i, L, R;
  if (n == 0) return;
  if (n == 1) {
    post[postL] = pre[preL];
    return;
  }
  //根结点数据为pre数组第一个元素的数据
  root = pre[preL];
  // post数组最后一个元素应为根节点的数据
  post[postL + n - 1] = root;
  //在in数组找到与根节点数据相同的元素下标
  for (i = 0; i < n; i++)
    if (in[inL + i] == root) break;
  L = i;
  R = n - L - 1;
  //对左子树求解
  //左子树pre数组起始位置应为根节点后一个位置(preL+1)
  //左子树in数组起始位置为根结点左侧，因此起始位置不变(inL)
  //左子树数据应在post数组最前面，因此起始位置不变(postL)
  //左子树总节点数为L
  Solve(preL + 1, inL, postL, L);
  //对右子树求解
  //右子树pre数组起始位置应为左子树最后一个元素的下一个位置(preL+L+1)
  //右子树in数组起始位置为根结点右侧，而根结点左侧有L个左子树的元素，因此确定位置(inL+L+1)
  //右子树数据应在post数组L个左子树部分的后一个位置(postL+L)
  //右子树总节点数为R
  Solve(preL + L + 1, inL + L + 1, postL + L, R);
}

//获取字符串中的数字
int GetInputNum(char input[]) {
  int result = 0, i, temp;
  for (i = 3; i < strlen(input); i++) {
    if (input[i] >= '0' && input[i] <= '9') {
      temp = (int)(input[i] - '0');
      result = result * 10 + temp;
    }
  }
  return result;
}

int main() {
  char input[100] = " ", temp[100] = " ";
  int N, i, preCount = 0, inCount = 0, popResult, num;
  scanf("%d\n", &N);
  Stack S = CreateStack(N);

  for (i = 0; i < 2 * N; i++) {
    fgets(input, sizeof(input), stdin);
    strncpy(temp, input, 3);
    //入栈
    if (!strcmp(temp, "Pus")) {
      num = GetInputNum(input);
      Push(S, num);
      pre[preCount] = num;
      preCount++;
    }
    //出栈
    if (!strcmp(temp, "Pop")) {
      popResult = Pop(S);
      in[inCount] = popResult;
      inCount++;
    }
  }
  Solve(0, 0, 0, N);
  PrintResult(N);
  return 0;
}