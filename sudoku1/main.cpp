#include <stdio.h>

#define MAXN 33

int n;
unsigned long long k;

char mat[MAXN][MAXN];

int getCompletion(int left, int up, int upandleft){
  if(left!=up) return upandleft;
  else{
    if(left==upandleft%3+1) return (upandleft%3+1)%3+1;
    else return upandleft%3+1;
  }
}

int main(){
  FILE *fin, *fout;
  fin = fopen("sudoku1.in", "r");
  fscanf(fin, "%d %llu\n", &n, &k);
  fclose(fin);

  unsigned long long y = ((unsigned long long)1<<(2*(n-1)));
  unsigned long long x = 3*y;
  for(int i=0; i<n; i++){
    if(y>0)mat[0][i] = ((unsigned long long)k/y-((unsigned long long)k%y==0))%3+1;
    else mat[0][i] = 1;
    if(i>0 && mat[0][i]>=mat[0][i-1]) mat[0][i] = mat[0][i]%3 + 1;
    k=k%y+(k%y==0)*y;
    y/=2;
  }
  for(int i=1; i<n; i++){
    mat[i][0] = ((unsigned long long)k/y-((unsigned long long)k%y==0))%3+1;
    if(mat[i][0] >= mat[i-1][0]) mat[i][0] = mat[i][0]%3 + 1;
    k=k%y+(k%y==0)*y;
    y/=2;
  }
  for(int i=1; i<n; i++){
    for(int j=1; j<n; j++){
      mat[i][j] = getCompletion(mat[i][j-1], mat[i-1][j], mat[i-1][j-1]);
    }
  }

  fout = fopen("sudoku1.out", "w");
  fprintf(fout, "%llu\n", x);
  for(int i=0; i<n; i++){
    for(int j=0; j<n; j++){
      fprintf(fout, "%d ", mat[i][j]);
    }
    fprintf(fout, "\n");
  }
  fclose(fout);
  return 0;
}
