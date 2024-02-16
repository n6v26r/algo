#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>

#define MAXSIZE 1000

int mat[MAXSIZE+1][MAXSIZE+1];
int n, m;

int section(int l1, int c1, int l2, int c2){
  int val = mat[l2][c2]-(c1>0?mat[l2][c1-1]:0)-(l1>0?mat[l1-1][c2]:0)+(l1>0&&c1>0?mat[l1-1][c1-1]:0);
  return val;
}

int _exp(int b, int e){
  int p = 1;
  while(e>0){
    if(e%2){
      p=(p*b)%1001;
    }
    b=(b*b)%1001;
    e/=2;
  }
  return p;
}

void readInt(int *n, FILE *fin){
  *n = 0;
  char c=fgetc(fin);
  while(!isdigit(c)) c = fgetc(fin);
  while(isdigit(c)){
    *n = (*n)*10+c-'0';
    c=fgetc(fin);
  }
}

int main(){
  int q;
  FILE* fin, *fout;
  fin=fopen("paint.in", "r");
  fout=fopen("paint.out", "w");
  fscanf(fin, "%d %d\n", &n, &m);
  for(int i=0; i<n; i++){
    for(int j=0; j<m; j++){
      mat[i][j] = fgetc(fin)-'0'; fgetc(fin); 
      mat[i][j] = 1-mat[i][j];
      mat[i][j]+=(i>0?mat[i-1][j]:0)+(j>0?mat[i][j-1]:0)-(i>0 && j>0?mat[i-1][j-1]:0);
    }fgetc(fin);
  }
  fscanf(fin, "%d", &q);
  for(int i=0; i<q; i++){
    int lstart, cstart, lend, cend;
    readInt(&lstart, fin);
    readInt(&cstart, fin);
    readInt(&lend, fin);
    readInt(&cend, fin);
    lstart--; cstart--; lend--; cend--;
    fprintf(fout, "%d\n", _exp(2, section(lstart, cstart, lend, cend)));
  }
  fclose(fin);

  fclose(fout);
  return EXIT_SUCCESS;
}
