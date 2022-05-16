#include <math.h>
#include <stdio.h>

#define IslandRadius (15.0 / 2) /*radius of the island*/
#define SquareSize (100)        /*size of lake(square)*/
#define MaxCrocodiles (107)     /* Max number of crocodiles */
#define YES 1
#define NO 0

typedef struct Point {
  double x, y;
} Position;

int visited[MaxCrocodiles];
Position P[MaxCrocodiles];
int N, D;

/*reach bank from current position*/
int IsSafe(int V) {
  return (abs(P[V].x) >= SquareSize / 2 - D ||
          abs(P[V].y) >= SquareSize / 2 - D);
}

/*if he can jump from current position to next position*/
int Jump(int V1, int V2) {
  return sqrt((P[V1].x - P[V2].x) * (P[V1].x - P[V2].x) +
              (P[V1].y - P[V2].y) * (P[V1].y - P[V2].y)) <= D;
}

int DFS(int V) {
  visited[V] = 1;
  int answer = NO;
  if (IsSafe(V))
    answer = YES;
  else {
    for (int i = 0; i < N; i++)
      if (!visited[i] && Jump(V, i)) {
        answer = DFS(i);
        if (answer == YES) break;
      }
  }
  return answer;
}

/*return 1 if James Bond can reach v at the first jump*/
int FirstJump(int Idx) {
  return sqrt(P[Idx].x * P[Idx].x + P[Idx].y * P[Idx].y) <= IslandRadius + D;
}

void Save007() {
  int answer = NO;
  for (int i = 0; i < N; i++) {
    if (!visited[i] && FirstJump(i)) {
      answer = DFS(i);
      if (answer == YES) break;
    }
  }
  if (answer == YES)
    puts("Yes");
  else
    puts("No");
}

int main() {
  scanf("%d %d", &N, &D);
  for (int i = 0; i < N; i++) scanf("%lf %lf", &P[i].x, &P[i].y);
  for (int i = 0; i < N; i++) visited[i] = 0;
  Save007();
  return 0;
}
