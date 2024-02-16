#include <stdio.h>
#include <string.h>

#define MAXN 505
#define MAXK 250009
#define MOD 999979

int dp[2][MAXK];
int v[MAXN];

int k, n;

int main(){
  FILE *fin, *fout;
  fin = fopen("rucsac.in", "r");
  fscanf(fin, "%d%d", &n, &k);
  for(int i=1; i<=n; i++){
    fscanf(fin, "%d", &v[i]);
  }
  fclose(fin);
  
  dp[0][0] = 1;

  for(int i=1; i<=n; i++){
    for(int j=0; j<=k; j++){
      dp[i%2][j] = (j>=v[i]?dp[(i-1)%2][j-v[i]]:0)+dp[(i-1)%2][j];
      if(dp[i%2][j]>MOD) dp[i%2][j]-=MOD;
    }
  }

  fout = fopen("rucsac.out", "w");
  fprintf(fout, "%d\n", dp[n%2][k]);
  fclose(fout);
  return 0;
}
