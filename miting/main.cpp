#include <stdio.h>
#include <stdbool.h>

#define MAXN 60
#define MAXK 10
#define DIR 4
#define QUEUESIZE 1100000
#define INF 9999
#define BORDER '#'
#define MIN(a, b) ((a)<(b)?(a):(b))

typedef struct{
  int lin;
  int col;
}node;

typedef struct{
  node v[QUEUESIZE+1];
  int u;
  int p;
}queue;

int p, n, m;
char mat[MAXN+3][MAXN+3];
int dp[MAXK+1][MAXK+1][MAXN+3][MAXN+3];
node cars[MAXK+1];
int dirLin[DIR] = {-1, 0, 1, 0};
int dirCol[DIR] = {0, 1, 0, -1};
queue q;

char s[MAXN];

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

void bfs(int i, int j){
  while(!isEmpty(&q)){
    node active = bottom(&q);
    // printf("%d %d\n", active.lin, active.col);
    int dist = dp[i][j][active.lin][active.col];
   
    for(int d=0; d<DIR; d++){
      node _new = {active.lin+dirLin[d], active.col+dirCol[d]};
   
      if(mat[_new.lin][_new.col]==BORDER) continue; 
      if(dp[i][j][_new.lin][_new.col]<=dist+1) continue;
     
      add(&q, _new);
      dp[i][j][_new.lin][_new.col] = dist+1;
    }
  }
}

int main(){
  node start = {INF, INF};
  node end = {0, 0};
  FILE *fin, *fout;
  fin=fopen("miting.in", "r");
  fscanf(fin, "%d %d %d\n", &p, &n, &m);
  char c = fgetc(fin);
  int k=0;
  while(c!='\n'){
    s[k++] = c;
    c=fgetc(fin);
  }
  int adder = 0;
  for(int i=1; i<=n; i++){
    for(int j=1; j<=m; j++){
      mat[i][j] = fgetc(fin);
      if(mat[i][j]!=BORDER && mat[i][j]!='_'){
        cars[adder++] = (node){i, j};
        if(i<start.lin) start.lin = i;
        if(i>end.lin) end.lin = i;
        if(j<start.col) start.col = j;
        if(j>end.col) end.col = j;
      }
    }
    fgetc(fin);
  }

  for(int i=0; i<=n+1; i++){
    mat[i][0] = mat[i][m+1] = BORDER;
  }

  for(int i=0; i<=m+1; i++){
    mat[0][i] = mat[n+1][i] = BORDER;
  }
  fclose(fin);

  // for(int i=1; i<=n; i++){
  //   for(int j=1; j<=m; j++){
  //     printf("%c", mat[i][j]);
  //   }
  //   printf("\n");
  // }

  // for(int lvl=0; lvl<3; lvl++){
  //   for(int i=1; i<=n; i++){
  //     for(int j=1; j<=m; j++){
  //       printf("%d ", dp[i][j][i][j]);
  //     }
  //     printf("\n");
  //   }
  //   printf("\n\n");
  // }
  //
  for(int i=0; i<k; i++){
    for(int l=1; l<=n; l++){
      for(int c=1; c<=m; c++){
        dp[i][i][l][c] = INF;
      }
    }
    add(&q, cars[i]);
    dp[i][i][cars[i].lin][cars[i].col] = 0;
    bfs(i, i);
    // printf("[%d]\n", i);
  //   for(int l=1; l<=n; l++){
  //     for(int c=1; c<=m; c++){
  //       if(mat[l][c]==BORDER) printf("## ");
  //       else
  //         printf("%2d ", dp[i][i][l][c]);
  //     }
  //     printf("\n");
  //   }
  }

  for(int size=2; size<=k; size++){
    for(int i=0; i<=k-size; i++){
      q.p = 0;
      q.u = 0;
      int j = i+size-1;
      printf("[%d %d]\n", i, j);

      for(int l=1; l<=n; l++){
        for(int c=1; c<=m; c++){
          if(mat[l][c]==BORDER){ continue;}
          dp[i][j][l][c] = INF;
          int min = dp[i][j][l][c];
          // int minsp = 0;
          for(int a=i; a<j; a++){
            // if(dp[i][a][l][c]+dp[a+1][j][l][c]<min) minsp = a;
            min = MIN(min, dp[i][a][l][c]+dp[a+1][j][l][c]);
          }

          dp[i][j][l][c] = min;
          printf("%2d ", dp[i][j][l][c]);
          // printf("\nP:%d %d\n", q.p, q.u);
          add(&q, (node){l, c});
          dp[i][j][l][c] = min;
        }
        printf("\n");
      }
      bfs(i, j);
    }
  }

  fout = fopen("miting.out", "w");
  if(p==1){
    // printf("%d %d %d %d\n", start.lin, start.col, end.lin, end.col);
    fprintf(fout, "%d\n", (end.lin-start.lin+1)*(end.col-start.col+1));
  }
  else{
    int min = INF;
    for(int i=1; i<=n; i++){
      for(int j=1; j<=m; j++){
        if(mat[i][j]==BORDER) continue;
        if(dp[0][k-1][i][j]<min)
          min = dp[0][k-1][i][j];
      }
    }
    fprintf(fout, "%d\n", min);
  }
  fclose(fout);
  return 0;
}
