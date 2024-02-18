#include <stdio.h>
#include <limits.h>

#define MAXN 505

int n, k;
int mat[MAXN][MAXN];

int zone(int i, int j, int l, int c){
  return mat[l][c]-mat[i-1][c]-mat[l][j-1]+mat[i-1][j-1];
}

int main(){
  FILE *fin, *fout;
  fin = fopen("cruce.in", "r");
  fscanf(fin, "%d%d", &n, &k);
  for(int i=1; i<=n; i++){
    for(int j=1; j<=n; j++){
      fscanf(fin, "%d", &mat[i][j]);
      mat[i][j] += mat[i-1][j]+mat[i][j-1]-mat[i-1][j-1];
    }
  }
  fclose(fin);

  int max=-INT_MAX, l=0, c=0;
  for(int lin=1; lin+k-1<=n; lin++){
    int valLin = zone(lin, 1, lin+k-1, n);
    for(int col=1; col+k-1<=n; col++){
      int valCol = zone(1, col, n, col+k-1);
      if(valLin+valCol - zone(lin, col, lin+k-1, col+k-1)>max){
        max = valLin+valCol - zone(lin, col, lin+k-1, col+k-1);
        l = lin;
        c = col;
      }
    }
  }

  fout = fopen("cruce.out", "w");
  fprintf(fout, "%d %d %d\n", max, l, c);
  fclose(fout);
  return 0;
}