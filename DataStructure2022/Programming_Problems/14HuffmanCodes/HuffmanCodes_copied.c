/*
copy from:
https://blog.csdn.net/shenbossed/article/details/106253811
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define Maxsize 64

char ch[Maxsize];
int N, w[Maxsize], TotalCodes;

typedef struct TreeNode *Huffman;
struct TreeNode {
  int weight;
  Huffman left, right;
};

typedef struct HeapNode *MinHeap;
struct HeapNode {
  Huffman data[Maxsize];
  int size;
};

MinHeap CreateHeap();
Huffman CreateHuffman();
void Insert(MinHeap H, Huffman x);
Huffman DeleteMin(MinHeap H);
Huffman BuildHuffman(MinHeap H);
int WPL(Huffman root, int depth);
int judge();
int main() {
  int M;
  Huffman tmp, root;
  scanf("%d", &N);
  MinHeap H = CreateHeap();
  for (int i = 0; i < N; i++) {
    // getchar();
    scanf(" %c %d", &ch[i], &w[i]);
    tmp = CreateHuffman();
    tmp->weight = w[i];
    Insert(H, tmp);
  }
  root = BuildHuffman(H);
  TotalCodes = WPL(root, 0);
  scanf("%d", &M);
  for (int i = 0; i < M; i++) {
    if (judge())
      printf("Yes\n");
    else
      printf("No\n");
  }
  return 0;
}
MinHeap CreateHeap() {
  MinHeap H;
  H = (MinHeap)malloc(sizeof(struct HeapNode));
  H->size = 0;
  H->data[0] = (Huffman)malloc(sizeof(struct TreeNode));
  H->data[0]->left = H->data[0]->right = NULL;
  H->data[0]->weight = -1;
  return H;
}
Huffman CreateHuffman() {
  Huffman H;
  H = (Huffman)malloc(sizeof(struct TreeNode));
  H->left = H->right = NULL;
  H->weight = 0;
  return H;
}
void Insert(MinHeap H, Huffman x) {
  int i = ++H->size;
  while (x->weight < H->data[i / 2]->weight) {
    H->data[i] = H->data[i / 2];
    i /= 2;
  }
  H->data[i] = x;
}
Huffman DeleteMin(MinHeap H) {
  Huffman Mintem, temp;
  int parent, child;
  Mintem = H->data[1];
  temp = H->data[H->size--];
  for (parent = 1; parent * 2 <= H->size; parent = child) {
    child = parent * 2;
    if ((child != H->size) &&
        (H->data[child]->weight > H->data[child + 1]->weight))
      child++;
    if (temp->weight <= H->data[child]->weight)
      break;
    else {
      H->data[parent] = H->data[child];
    }
  }
  H->data[parent] = temp;
  return Mintem;
}
Huffman BuildHuffman(MinHeap H) {
  Huffman T;
  int num = H->size;
  for (int i = 1; i < num; i++) {
    T = CreateHuffman();
    T->left = DeleteMin(H);
    T->right = DeleteMin(H);
    T->weight = T->left->weight + T->right->weight;
    Insert(H, T);
  }
  T = DeleteMin(H);
  return T;
}
int WPL(Huffman root, int depth) {
  if ((root->left == NULL) && (root->right == NULL))
    return depth * root->weight;
  else
    return WPL(root->left, depth + 1) + WPL(root->right, depth + 1);
}
int judge() {
  Huffman T, p;
  char ch1, *codes;
  int length = 0, flag = 1, j, wgh;
  codes = (char *)malloc(sizeof(char) * Maxsize);
  T = CreateHuffman();
  for (int i = 0; i < N; i++) {
    scanf("\n%c %s", &ch1, codes);
    if (strlen(codes) >= N)  //代码长度大于字符总个数
      flag = 0;
    else {
      for (j = 0; ch1 != ch[j]; j++)
        ;          //找到对应的字母
      wgh = w[j];  //对应的频率
      p = T;
      for (j = 0; j < strlen(codes); j++) {
        if (codes[j] == '0')  //建立左子树
        {
          if (!p->left) p->left = CreateHuffman();
          p = p->left;

        } else if (codes[j] == '1')  //建立右子树
        {
          if (!p->right) p->right = CreateHuffman();
          p = p->right;
        }
        if (p->weight) flag = 0;  //此节点已经有权重了，不符合前缀码要求
      }
      if (p->left || p->right)  //不是叶子结点
        flag = 0;
      else
        p->weight = wgh;  //这个节点给予权重
    }
    length += strlen(codes) * p->weight;  //权重进行累加
  }
  if (length != TotalCodes)  //累加的权重如果不等于最后的总权重
    flag = 0;
  return flag;
}