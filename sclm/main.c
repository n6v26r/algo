#include <stdio.h>
 
#define MAXN 1024
 
char a[MAXN+1];
char b[MAXN+1];
 
int mat[MAXN+1][MAXN+1];
 
int max=0, l=-1, c=-1;
 
int main(){
  int n, m;
  FILE *fin, *fout;
  fin=fopen("sclm.in", "r");
  fscanf(fin, "%d%d\n", &n, &m);
  for(int i=0; i<n;i++){
    a[i]=fgetc(fin);
  }fgetc(fin);
  for(int i=0; i<m;i++){
    b[i]=fgetc(fin);
  }
  fclose(fin);
 
  int max=0; int am=-1; int bm=-1;
 
  for(int i=1; i<=n; i++){
    for(int j=1; j<=m; j++){
      if(a[i-1]==b[j-1])
        mat[i][j] = mat[i-1][j-1]+1;
      else{
        mat[i][j]=0;
      }
      if(mat[i][j]>max){
        max=mat[i][j], am=i, bm=j;
      }
    }
  }
 
  fout=fopen("sclm.out", "w");
  fprintf(fout, "%d %d %d\n", max, am-max+1, bm-max+1);
  fclose(fout);
  return 0;
}
