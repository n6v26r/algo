// __razv was here
#include <stdio.h>
#define MAXN 327

int n;

int mat[MAXN][MAXN];

int main(){
  FILE *fin, *fout;
  fin = fopen("maximumsum.in", "r");
  fscanf(fin, "%d", &n);
  for(int i=0; i<n; i++){
    for(int j=0; j<n; j++){
      fscanf(fin, "%d", &mat[i][j]);
      mat[i][j]+=(j>0?mat[i][j-1]:0);
    }
  }
  fclose(fin);
  //
  // for(int i=0; i<n; i++){
  //   for(int j=0; j<n; j++){
  //     printf("%d ", mat[i][j]);
  //   }printf("\n");
  // }
  int maxSubmat = 0;
  for(int a=0; a<n; a++){
    for(int b=a; b<n; b++){
      int maxHere = 0, max = 0;
      // printf("%d %d: ", a, b);
      for(int j=0; j<n; j++){
        int val = mat[j][b] - (a>0?mat[j][a-1]:0);
        // printf("%d ", val);
        maxHere = maxHere + val;
        if(maxHere>max) max = maxHere;
        if(maxHere<0) maxHere = 0;
      }
      // printf("\n");
      if(max>maxSubmat) maxSubmat = max;
    }
  }

  fout = fopen("maximumsum.out", "w");
  fprintf(fout, "%d\n", maxSubmat);
  fclose(fout);
}
