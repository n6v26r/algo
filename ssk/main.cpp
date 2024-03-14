#pragma GCC optimize("Ofast,unroll-loops")
#include <stdio.h>

#define MAXN 155
#define MAXVAL 1001

int mat[MAXN][MAXN];
int n, m, k;

inline int get(int i, int j, int l, int c){
  return (mat[l][c]-(i>0?mat[i-1][c]:0)-(j>0?mat[l][j-1]:0)+
         (i>0 && j>0?mat[i-1][j-1]:0));
}

int sml(int val){
  int total = 0;
  for(int i=0; i<m; i++){
    for(int j=i; j<m; j++){
      int s = 0;
      int d = 0;
      while(s<n){
        while(d<n &&  get(s, i, d, j)<val)
          d++;

        total += (d-s);
        s++;
      }
    }
  }
  return total+1;
}

int binsearch(int val){
  int s = 0;
  int d = MAXN*MAXN*MAXVAL;
  while(d-s>1){
    int m = (s+d)/2;
    if(sml(m)>val) d = m;
    else s = m;
  }
  return s;
}

int main(){
  FILE *fin, *fout;
  fin = fopen("ssk.in", "r");
  fscanf(fin, "%d%d%d", &n, &m, &k);
  for(int i=0; i<n; i++){
    for(int j=0; j<m; j++){
      fscanf(fin, "%d", &mat[i][j]);
      mat[i][j] += (i>0?mat[i-1][j]:0) + (j>0?mat[i][j-1]:0) - (i>0 && j>0?mat[i-1][j-1]:0);
    }
  }
  fclose(fin);

  fout = fopen("ssk.out", "w");
  fprintf(fout, "%d\n", binsearch(k));
  fclose(fout);
  return 0;
}
