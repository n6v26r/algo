#include <stdio.h>

#define MAXN 1001
#define MIN(a, b) ((a)<(b)?(a):(b))

typedef struct{
  int lin;
  int col;
}matrix;

int dp[MAXN][MAXN];

int n;

// O(n^3) time
int optimizeMultiplication(int a, int b, matrix* chain){
  if(b-a==1){
    return chain[a].lin*chain[a].col*chain[b].col;
  }
  else if(b==a) return 0;

  if(!dp[a][b]){
    int cost = __INT_MAX__;
    for(int i=a; i<b; i++){
      int newCost = optimizeMultiplication(a, i, chain) + optimizeMultiplication(i+1, b, chain) + 
                    chain[a].lin*chain[i].col*chain[i+1].col;
      cost = MIN(cost, newCost);
    }
    dp[a][b] = cost;
  }

  return dp[a][b];
}

matrix chain[MAXN];

int main(){
  FILE *fin, *fout;
  fin = fopen("matrixchain.in", "r");
  fscanf(fin, "%d", &n);
  for(int i=0; i<n; i++){
    fscanf(fin, "%d%d", &chain[i].lin, &chain[i].col);
  }
  fclose(fin);
  int bestCost = optimizeMultiplication(0, n-1, chain); // [i, j]

  fout = fopen("matrixchain.out", "w");
  fprintf(fout, "%d\n", bestCost);
  fclose(fout);
  return 0;
}
