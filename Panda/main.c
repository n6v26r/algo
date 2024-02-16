#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define MAXSIZE 500
#define BORDER -1
#define INF __INT_MAX__
#define FOOD INF
#define DIR 4
#define QUEUESIZE 131072

typedef struct{
  int min;
  int count;
} _bfs;

typedef struct{int lin; int col;} node;

typedef struct{node v[QUEUESIZE+1]; int u; int p;}queue;

int p, n, m, t, l, c, k, s;
int mat[MAXSIZE+3][MAXSIZE+3];
int food[MAXSIZE+1][MAXSIZE+3];
int pow2[] = {1, 2, 4, 8, 16, 32, 64, 128, 256, 512, 1024, 2048, 4096};
int dirLin[DIR] = {-1, 0, 1, 0};
int dirCol[DIR] = {0, 1, 0, -1};
queue q; // queue

//
// QUEUE OPERATIONS
//
void add(queue* q, node val){
  q->p = (q->p+1)%QUEUESIZE;
  q->v[q->p] = val;
}

void yeet(queue* q){
  q->u = (q->u+1)%QUEUESIZE;
}

bool isEmpty(queue *q){
  return q->p==q->u;
}

node bottom(queue *q){
  node bottom = q->v[q->u+1];
  yeet(q);
  return bottom;
}
//
//
//

bool checkAccess(int a, int k, int s){
  return (((-1)<<s)|(a%pow2[s]))==(~(k%pow2[s])); // check if the last s binary digits are each other's complement
}

_bfs bfs(int lin, int col){
  q.p = q.u = 0;
  
  int mindist = INF;
  int count = 0;
  
  if(food[lin][col] == FOOD) return (_bfs){0, 1};
  add(&q, (node){lin, col});
  food[lin][col] = 1;

  while(!isEmpty(&q)){
    node active = bottom(&q);
    int dist = food[active.lin][active.col];
   
    for(int i=0; i<DIR; i++){
      node _new = {active.lin+dirLin[i], active.col+dirCol[i]};
      
      if(mat[_new.lin][_new.col]==BORDER || !checkAccess(mat[_new.lin][_new.col], k, s)) continue; 
      if(food[_new.lin][_new.col]<=dist+1) continue;
      
      if(food[_new.lin][_new.col]==FOOD){
        if(mindist == INF){mindist = dist+1; count=1;}
        else if(dist+1==mindist) count++;
      }
      
      if(mindist == INF){
        add(&q, _new);
      }
    
      food[_new.lin][_new.col] = dist+1;
    }
  }
  return (_bfs){mindist-1, count};
}

int main(){
  memset(food, 127, sizeof(food));
  FILE *fin, *fout;
  fin  = fopen("panda.in", "r");
  fscanf(fin, "%d\n%d %d %d\n %d %d %d %d\n", &p, &n, &m, &t, &l, &c, &k, &s);
  for(int i=0; i<t; i++){
    int lin, col;
    fscanf(fin, "%d %d\n", &lin, &col);
    food[lin][col] = FOOD;
  }
  for(int i=1; i<=n; i++){
    for(int j=1; j<=m; j++){
      fscanf(fin, "%d", &mat[i][j]);
    }
  }
  for(int i=0; i<=n+1; i++){
    mat[i][0] = mat[i][m+1] = BORDER;
  }
  for(int i=0; i<=m+1; i++){
    mat[0][i] = mat[n+1][i] = BORDER;
  }
  fclose(fin);

  fout  = fopen("panda.out", "w");
  if(p==1){
    int total = 0;
    for(int i=1; i<=n; i++){
      for(int j=1; j<=m; j++){
        if(checkAccess(mat[i][j], k, s) && !(i==l && j==c))
          total++;
      }
    }
    fprintf(fout, "%d\n", total);
  }
  else{
    _bfs result = bfs(l, c);
    fprintf(fout, "%d %d\n", result.min, result.count);
  }
  fclose(fout);
  return 0;
}
