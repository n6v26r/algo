#include <stdio.h>

#define MAXVAL 1001

int a, b;

int mat[MAXVAL][MAXVAL];
int v[MAXVAL*MAXVAL];

int main(){
  FILE *fin, *fout;
  fin = fopen("muzica.in", "r");
  fscanf(fin, "%d%d", &a, &b);
  fclose(fin);

  int size=0;
  while(!mat[a][b]){
    mat[a%b][b] = size+1;
    v[size++] = (a*10)/b;
    a=(a*10)%b;
  }
  int rsize = size-mat[a][b]+1;

  fout = fopen("muzica.out", "w");
  for(int i=0;i<size; i++)
    fprintf(fout, "%d", v[i]);
  fprintf(fout, " %d\n", rsize);
  fclose(fout);
  return 0;
}
