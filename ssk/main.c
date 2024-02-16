#include <stdio.h>
#include <stdlib.h>

#define MAXSIZE 150

int n, m, k;

int mat[MAXSIZE+1][MAXSIZE+1];

int getSum(int i, int j, int lin, int col){
  return mat[lin][col]  - (j>0?mat[lin][j-1]:0) - (i>0?mat[i-1][col]:0) + (i>0&&j>0?mat[i-1][j-1]:0);
}

int sml(int val){
  int count = 0;
  for(int i=0; i<n; i++){
    for(int j=i; j<n; j++){

      int st = 0;
      int dr = 0;
      while(st<m){
        while(dr<m && getSum(i, st, j, dr)<val){
          dr++;
        }
        count += dr-st;
        st++;
      }
    }
  }
  return count+1;
}

int main(){
  FILE *fin, *fout;
  fin = fopen("ssk.in", "r");
  fscanf(fin, "%d %d %d\n", &n, &m, &k);
  for(int i=0; i<n; i++){
    for(int j=0; j<m; j++){
      fscanf(fin, "%d ", &mat[i][j]);
      mat[i][j] += (i>0?mat[i-1][j]:0)+(j>0?mat[i][j-1]:0)-(i>0&&j>0?mat[i-1][j-1]:0);
    }
  }
  fclose(fin);
  int s = 0;
  int d = mat[n-1][m-1]+1;
  int m;
  while(d-s>1){
    m = (s+d)/2;
    if(sml(m)>k)
      d = m;
    else
     s = m;
  }

  fout = fopen("ssk.out", "w");
  fprintf(fout, "%d\n", s);
  fclose(fout);
  return EXIT_SUCCESS;
}
