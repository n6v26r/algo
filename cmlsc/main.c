#include <stdio.h>
#include <ctype.h>
 
#define MAXN 1024
 
int a[MAXN+1];
int b[MAXN+1];
 
char sens[MAXN+1][MAXN+1];
int mat[MAXN+1][MAXN+1];
 
int max=0, l=-1, c=-1;
 
 
void readInt(int *n, FILE* fin){
  char c = fgetc(fin);
  *n = 0;
  while(!isdigit(c))
    c=fgetc(fin);
  while(isdigit(c))
    (*n)=(*n)*10+c-'0', c=fgetc(fin);
}
 
int main(){
  int n, m;
  FILE *fin, *fout;
  fin=fopen("cmlsc.in", "r");
  fscanf(fin, "%d%d", &n, &m);
  for(int i=0; i<n;i++){
    readInt(&a[i], fin);
  }
  for(int i=0; i<m;i++){
    readInt(&b[i], fin);
  }
  fclose(fin);
 
  int max = 0;
 
  for(int i=0; i<n; i++){
    for(int j=0; j<m; j++){
      int ai; int aj; int aij;
      if(i==0 || j==0) aij=0; else aij = mat[i-1][j-1];
      if(i==0) ai = 0; else ai = mat[i-1][j];
      if(j==0) aj = 0; else aj = mat[i][j-1];
 
      if(a[i]==b[j])
        mat[i][j] = aij+1, sens[i][j]=2;
      else{
        if(ai>aj){mat[i][j]=ai; sens[i][j]=0;}
        else {mat[i][j]=aj; sens[i][j]=1;}
      }
      if(mat[i][j]>max)
        max=mat[i][j], l=i, c=j;
    }
  }
 
  fout=fopen("cmlsc.out", "w");
  int i=0;
  for(; l>=0 && c>=0;){
    int s = sens[l][c];
    if(s<2){
      l-=1-(s);
      c-=(s);
    }
    else{
      a[i++]=b[c];
      l--, c--;
    }
  }
  fprintf(fout, "%d\n", max);
  for(i--; i>=0; i--)
    fprintf(fout, "%d ", a[i]);
  fprintf(fout, "\n");
 
  fclose(fout);
  return 0;
}
