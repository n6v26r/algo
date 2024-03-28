#include <stdio.h>

#define MAXN 1000
#define MAX(a, b) ((a)>(b)?(a):(b))
#define MIN(a, b) ((a)<(b)?(a):(b))

int dp[MAXN][MAXN];
int n;

int main(){
  FILE *fin, *fout;
  fin = fopen("248.in", "r");
  fscanf(fin, "%d", &n);
  for(int i=0; i<n; i++){
    fscanf(fin, "%d", &dp[i][i]);
  }
  fclose(fin);

  int maxval = 0;
  for(int j=1; j<n; j++){
    for(int i=0; i+j<n; i++){
      dp[i][i+j] = 0;
      if(dp[i][i+j-1]==dp[i+j][i+j]) dp[i][i+j] = MAX(dp[i][i+j], dp[i+j][i+j]+1);
      if(dp[i+1][i+j]==dp[i][i]) dp[i][i+j] = MAX(dp[i][i+j], dp[i][i]+1);
      for(int k = i; k<i+j; k++){
        dp[i][i+j] = MAX(dp[i][i+j], (dp[i][k]==dp[k+1][i+j]?dp[i][k]+1:0));
      }
      maxval = MAX(maxval, dp[i][i+j]);
    }
  }

  fout = fopen("248.out", "w");
  fprintf(fout, "%d\n", maxval);
  fclose(fout);
  return 0;
}
