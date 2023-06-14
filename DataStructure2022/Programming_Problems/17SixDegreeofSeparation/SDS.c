#include <stdio.h>
#define MaxVertexNum 1005

typedef int Vertex; /* 用顶点下标表示顶点,为整型 */

/*edge*/
typedef struct Enode *PtrToEnode;
struct Enode {
  Vertex V1, V2;
};
typedef PtrToEnode Edge;

/* 邻接点的定义 */
typedef struct AdjVNode *PtrToAdjVNode;
struct AdjVNode {
  Vertex AdjV;        /* 邻接点下标 */
  PtrToAdjVNode Next; /* 指向下一个邻接点的指针 */
};

typedef struct Vnode {
  PtrToAdjVNode FirstEdge; /* 边表头指针 */
  DataType Data;           /* 存顶点的数据 */
  /* 注意：很多情况下，顶点无数据，此时Data可以不用出现 */
} AdjList[MaxVertexNum]; /* AdjList是邻接表类型 */

/* 图结点的定义 */
typedef struct GNode *PtrToGNode;
struct GNode {
  int Nv;    /* 顶点数 */
  int Ne;    /* 边数   */
  AdjList G; /* 邻接表 */
};

typedef PtrToGNode LGraph; /* 以邻接表方式存储的图类型 */

void SDS() {
  for (each V in G) {
    count = BFS();
    Output(count / n);
  }
}

int BFS(Vertex V) {}

int N, M;

int main() {
  scanf("%d %d", &N, &M);

  return 0;
}
