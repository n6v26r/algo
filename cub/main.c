// this crappy piece of code is provided to u
// by __razv

// https://www.nerdarena.ro/problema/cub
#include <stdio.h>
 
#define MAXN 21
#define QUEUESIZE (MAXN*MAXN*MAXN)
#define MAX(a, b) ((a)>(b)?(a):(b))
 
typedef struct{
  int dist;
  int val;
  int dir;
}prop;
 
typedef struct{
  int i;
  int j;
  int k;
}node;
 
int n, m;
 
int cube[MAXN][MAXN][MAXN];
prop dp[MAXN][MAXN][MAXN];
 
node q[QUEUESIZE]; int l=0, r=0;
node ans[3*MAXN];
 
int dirH[]   = {1, -1, 0, 0, 0, 0};
int dirLin[] = {0, 0, -1, 0, 1, 0};
int dirCol[] = {0, 0, 0, 1, 0, -1};
 
int inBounds(int i, int j, int k){
  return (0<=i && i<n && 0<=j && j<n && 0<=k && k<n);
}
 
void bfs(node start){
  q[r] = start; r++;
  dp[start.i][start.j][start.k] = (prop){1, cube[start.i][start.j][start.k], 1};

  while(r!=l){
    node curr = q[l];
    l = (l+1)%QUEUESIZE;
    for(int dir=0; dir<6; dir++){
      node next = {curr.i+dirH[dir],curr.j+dirLin[dir],curr.k+dirCol[dir]};
 
      if(!inBounds(next.i, next.j, next.k)) continue;
      if(dp[next.i][next.j][next.k].dist != 0) continue;

      dp[next.i][next.j][next.k].dist = dp[curr.i][curr.j][curr.k].dist+1;
      int max = -1;
      int i = next.i, j=next.j, k = next.k;
      if(i>0 && max<dp[i-1][j][k].val && dp[i-1][j][k].dist==dp[i][j][k].dist-1) {max = dp[i-1][j][k].val; dp[i][j][k].dir = 1;}
      if(j>0 && max<dp[i][j-1][k].val && dp[i][j-1][k].dist==dp[i][j][k].dist-1) {max = dp[i][j-1][k].val; dp[i][j][k].dir = 2;}
      if(k>0 && max<dp[i][j][k-1].val && dp[i][j][k-1].dist==dp[i][j][k].dist-1) {max = dp[i][j][k-1].val; dp[i][j][k].dir = 3;}
      dp[i][j][k].val = max+cube[i][j][k];
      
      q[r] = next;
      r = (r+1)%QUEUESIZE;
    }
  }  
}
 
int main(){
  FILE *fin, *fout;
  fin = fopen("cub.in", "r");
  fscanf(fin, "%d%d", &n, &m); 
  for(int p=0; p<m; p++){
    int i, j, k, val; fscanf(fin, "%d%d%d%d", &i, &j, &k, &val);
    i--; j--; k--;
    cube[i][j][k] = val;
  }
  fclose(fin);
  
  bfs((node){0, 0, 0});

  fflush(stdout);

  int i = 0;
  node prev= {n-1, n-1, n-1};
  while(!(prev.i==0 && prev.j==0 && prev.k==0)){
    ans[i++] = prev;
    switch(dp[prev.i][prev.j][prev.k].dir){
      case 3:
        prev.k--;
        break;
      case 2:
        prev.j--;
        break;
      case 1:
        prev.i--;
        break;
      default:
        printf("sudo rm -rf /*\n");
        break; 
    }
  }

  fout = fopen("cub.out", "w");
  fprintf(fout, "%d\n", dp[n-1][n-1][n-1].val);
  while(i>=0){
    fprintf(fout, "%d %d %d\n", ans[i].i+1, ans[i].j+1, ans[i].k+1);
    i--;
  }
  fclose(fout);
}
