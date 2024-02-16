#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAXSIZE 100
#define max(a,b) ((a)>(b)?(a):(b))

bool mat[MAXSIZE+1][MAXSIZE+1];
int n, m;

int main()
{
  int p;
  FILE *fin, *fout;
  fin=fopen("foto1.in", "r");
  fscanf(fin, "%d\n%d %d\n", &p, &n, &m);
  for(int i=0; i<n; i++){
    for(int j=0; j<m; j++){
      mat[i][j] = fgetc(fin)-'0';
      fgetc(fin);
    }
  }
  fclose(fin);

  int negre, maxnigga = 0;
  if(p==1){
    for(int i=0; i<n; i++){
      negre = 0;
      for(int j=0; j<m; j++){
        negre = (1-mat[i][j])*(negre+1);
        if(negre>maxnigga)
          maxnigga = negre;
      }
    }
  }

  int fulgere = 0, maxh=0, h;
  for(int i=0; i<n; i++){
    for(int j=0; j<m; j++){
      if(mat[i][j]){
        int lin=i, col=j;
        h=0;
        fulgere++;
        while(lin<n && col<m && mat[lin][col]!=0){
          h++;
          mat[lin][col] = 0;
          lin++;
          if(lin>=n) break;
          int lastcol = col;
          for(col=max(lastcol-1, 0); col<lastcol+1 && col<m && !mat[lin][col]; col++);
        }
      }
      if(h>maxh){
        maxh = h;
      }
    }
  }

  fout=fopen("foto1.out", "w");
  if(p==1)
    fprintf(fout, "%d\n", maxnigga);
  else
    fprintf(fout, "%d %d\n", fulgere, maxh);
  fclose(fout);
  return 0;
}
