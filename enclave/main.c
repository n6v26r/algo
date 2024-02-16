#include <stdio.h>
#include <ctype.h>
 
#define MAX 1000
#define BORDER 0
#define FILL 100
 
int mat[MAX+3][MAX+3];
 
int n, m;
int val;
int f;
 
int l, c; // globale, we love MEL
int vecin;
 
char enc;
 
int fill(){
 
  if(mat[l][c]!=val){
    if(mat[l][c]!=vecin)
      enc = 0;
    return 1;
  }
 
  int p = 0;
 
  mat[l][c] += FILL;
  if(mat[l+1][c]!=mat[l][c]){
    l++;
    p+=fill();
    l--;
  }
 
  if(mat[l-1][c]!=mat[l][c]){
    l--;
    p+=fill();
    l++;
  }
  if(mat[l][c+1]!=mat[l][c]){
    c++;
    p+=fill();
    c--;
  }
 
  if(mat[l][c-1]!=mat[l][c]){
    c--;
    p+=fill();
    c++;
  }
 
  return p;
}
 
 
void readInt(int* n, FILE *fin){
  char c = fgetc(fin);
  *n=0;
  while(!isdigit(c))
    c=fgetc(fin);
  while(isdigit(c)){
    *n=(*n)*10+c-'0';
    c=fgetc(fin);
  }
}
 
int main(){
  FILE *fin, *fout;
  fin=fopen("enclave.in", "r");
  fscanf(fin, "%d%d", &n, &m);
  for(int i=1; i<=n; i++){
    for(int j=1; j<=m; j++){
      readInt(&mat[i][j], fin);
    }
  }
  fclose(fin);
 
  for(int i=0; i<=n+1; i++){
    mat[i][0]=mat[i][m+1]=BORDER;
  }
  for(int i=0; i<=m+1; i++){
    mat[0][i]=mat[n+1][i]=BORDER;
  }
 
  int enclave = 0;
  int pmax = 0;
  for(int i=1; i<=n; i++){
    for(int j=1; j<=m; j++){
      if(mat[i][j]<=100){
        val = mat[i][j];
        f = mat[i][j]+FILL;
        enc = 1;
        l=i;
        c=j;
        vecin=mat[i][j-1];
        int p = fill();
        if(enc){
          if(p>pmax)
            pmax = p;
          enclave++;
        }
      }
    }
  }
 
  fout=fopen("enclave.out", "w");
  fprintf(fout, "%d %d\n", enclave, pmax);
  fclose(fout);
}
