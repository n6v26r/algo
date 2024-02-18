#include <stdio.h>

#define MAXN 1069

int n, m;
int mat[MAXN][MAXN];

int zone(int i, int j, int l, int c){
  //printf("%d %d %d %d\n", i, j, l, c); fflush(stdout);
  return mat[l][c]-mat[i-1][c]-mat[l][j-1]+mat[i-1][j-1];
}

int getSum(int l, int c, int k){
  if(k==0) return 0;
  int sens = 1;
  int sum = 0;
  if(k<0) sens = -1, k = -k;
  int jump = (k%2)?k/2+1:k/2;
  if(sens<0){
    sum+=zone(l-jump+1, c-jump+1, l, c);
    sum+=getSum(l-jump, c, -k/2);
    sum+=getSum(l, c-jump, -k/2);
    //printf("%d %d %d: %d\n", l, c, k, sum);
  }
  else{
    sum+=zone(l, c, l+jump-1, c+jump-1);
    sum+=getSum(l+jump, c, k/2);
    sum+=getSum(l, c+jump, k/2);
    //printf("%d %d %d: %d\n", l, c, k, sum);
  }
  return sum;
}

int main(){
  int max = 0;
  FILE *fin, *fout;
  fin = fopen("triunghi.in", "r");
  fscanf(fin, "%d\n", &n);
  for(int i=1; i<=n; i++){
    for(int j=1; j<=n; j++){
      fscanf(fin, "%d", &mat[i][j]);
      mat[i][j] += mat[i-1][j]+mat[i][j-1]-mat[i-1][j-1];
    }
  }

  /*for(int i=1; i<=n; i++){
    for(int j=1; j<=n; j++)
      printf("%2d ", mat[i][j]);
    printf("\n");
  }*/

  fscanf(fin, "%d", &m);
  for(int i=0; i<m; i++){
    int l, c, k; fscanf(fin, "%d%d%d", &l, &c, &k);
    int sum = getSum(l, c, k);
    //printf("%d\n", sum);
    if(sum>max) max = sum;
  }
  fclose(fin);

  fout = fopen("triunghi.out", "w");
  fprintf(fout, "%d\n", max);
  fclose(fout);
  return 0;
}