#include <stdio.h>
#include <string.h>

#define MAXN 10001

#define MIN(a, b) ((a)<(b)?(a):(b))

int n, k;
int v[MAXN];

int dp[3][MAXN];

void dinamica(){
  dp[0][1] = v[0];
  dp[1][1] = MIN(v[1], v[0]);
  for(int i=2; i<n; i++){
    dp[i%3][1] = MIN(dp[(i-1)%3][1], v[i]);
    // if(i>=9898)
      // printf("%d 1: %d\n", i, dp[i%3][1]);
    for(int k=2; k<=(i+1)/2+(i+1)%2; k++){
      dp[i%3][k] = MIN(dp[(i-1)%3][k], dp[(i-2)%3][k-1]+v[i]);
      // if(i==9899 && dp[i%3][k]!=dp[(i-1)%3][k])
        // printf("%d %d (%d)\n", dp[i%3][k], dp[(i-1)%3][k], k);
      // printf("%d %d: %d\n", i, k, dp[i%3][k]); fflush(stdout);
    }
    for(int j=0; j<MAXN; j++) dp[(i-2)%3][j] = __INT_MAX__;
  }
}

void skip(int *v){
  v = (v+1);
}

void reset(){
  for(int i=0; i<3; i++){
    for(int j=0; j<MAXN; j++)
      dp[i][j] = __INT_MAX__;
  }
}

int main(){
  FILE *fin, *fout;
  fin = fopen("kds.in", "r");
  fscanf(fin, "%d%d", &n, &k);
  int sum = 0;
  for(int i=0; i<n; i++)
    fscanf(fin, "%d", &v[i]), sum+=v[i];
  fclose(fin);
  
  reset();
  dinamica();
  int a = dp[(n-2)%3][k];
  printf("%d, %d\n", a, dp[(n-1)%3][k]);
  skip(v);
  n--;
  
  reset();
  dinamica();
  int b = dp[(n-1)%3][k];
  printf("%d\n", b);

  fout = fopen("kds.out", "w");
  fprintf(fout, "%d\n", sum-MIN(a, b));
  fclose(fout);
}
