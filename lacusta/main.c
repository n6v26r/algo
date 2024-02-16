#include <limits.h>
#include <stdint.h>
#include <stdio.h>

#define MAXN 102
#define MIN(a, b) ((a)<(b)?(a):(b))

int n, m;
int mat[MAXN][MAXN];
int down[MAXN][MAXN];
int dp[MAXN][MAXN];

int main(){
  FILE *fin, *fout;
  fin = fopen("lacusta.in", "r");
  fscanf(fin, "%d%d", &n, &m);
  for(int i=0; i<n; i++){
    for(int j=0; j<m; j++){
      fscanf(fin, "%d", &mat[i][j]);
    }
  }
  fclose(fin);

  down[1][0] = __INT_MAX__;

  for(int i=0; i<n; i++){
    for(int j=0; j<m; j++){
      if(i==0){down[i][j] = mat[i][j]; continue;}
      if(i==1){if(j>0)down[i][j] = mat[0][j]+mat[0][0]+mat[1][j];continue;}
      int min = __INT_MAX__;
      for(int y=0; y<m; y++){
        if(y==j || down[i-1][y]==__INT_MAX__) continue;
        min = MIN(min, down[i-1][y]+mat[i-1][j]+mat[i][j]); 
      }
      down[i][j] = min;
    }
    for(int j=0; j<m; j++){
      if(i==0){if(j==0)dp[i][j] = mat[i][j]; else dp[i][j] = mat[0][0]+mat[i][j];continue;}
      
      int min = __INT_MAX__;
      for(int y=0; y<m; y++){
        if(down[i][y]==__INT_MAX__ || y==j) continue;
        else min = MIN(min, down[i][y]+mat[i][j]);
      }
      dp[i][j] = min;
    }
  }

  fout = fopen("lacusta.out", "w");
  fprintf(fout, "%d\n", dp[n-1][m-1]);
  fclose(fout);
  return 0;
}
