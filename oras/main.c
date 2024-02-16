#include <stdio.h>
 
#define MAX 200
#define BORDER '.'
#define FILL_P 2
#define FILL_C 3
#define FILL 1
 
int l, c; // globale, because MLE
 
char mat[MAX+3][MAX+3];
  int n, m;
 
int fill_o(){
  if(mat[l][c] == BORDER)
    return 0;
 
  mat[l][c] = FILL;
 
  int p = mat[l+1][c]   == BORDER
       || mat[l+1][c+1] == BORDER
       || mat[l+1][c-1] == BORDER
 
       || mat[l][c+1] == BORDER
       || mat[l][c-1] == BORDER
 
       || mat[l-1][c]   == BORDER
       || mat[l-1][c+1] == BORDER
       || mat[l-1][c-1] == BORDER;
 
  if(mat[l][c+1]!=FILL){
    c++; // incepe distractia
    p+= fill_o();
    c--;
  }
  if(mat[l][c-1]!=FILL){
    c--;
    p+= fill_o();
    c++;
  }
  if(mat[l-1][c]!=FILL){
    l--;
    p+= fill_o();
    l++;
  }
  if(mat[l-1][c+1]!=FILL){
    l--;
    c++;
    p+= fill_o();
    l++;
    c--;
  }
  if(mat[l-1][c-1]!=FILL){
    l--;
    c--;
    p+= fill_o();
    c++;
    l++;
  }
  if(mat[l+1][c]!=FILL){
    l++;
    p+= fill_o();
    l--;
  }
  if(mat[l+1][c+1]!=FILL){
    l++;
    c++;
    p+= fill_o();
    l--;
    c--;
  }
  if(mat[l+1][c-1]!=FILL){
    l++;
    c--;
    p+= fill_o();
    l--;
    c++;
  }
 
  return p;
}
 
void fill_c(){
  if(mat[l][c] != 'C')
    return;
 
  mat[l][c] = FILL_C;
 
  l++;
  fill_c();
  l--;


  l--;
  fill_c();
  l++;


  c++;
  fill_c();
  c--;


  c--;
  fill_c();
  c++;
 
}
 
int fill_p(){
  if(mat[l][c] != 'P')
    return 0;
 
  int a = 1;
  mat[l][c] = FILL_P;
 
  l++;
  a+=fill_p();
  l--;

  l--;
  a+=fill_p();
  l++;


  c++;
  a+=fill_p();
  c--;


  c--;
  a+=fill_p();
  c++;
 
  return a;
}
 
 
int main(){
  int lo=0, co=0;
  FILE *fin, *fout;
  fin=fopen("oras.in", "r");
  fscanf(fin, "%d%d\n", &n, &m);
  for(int i=1; i<=n; i++){
    for(int j=1; j<=m; j++){
      mat[i][j] = fgetc(fin);
      if(mat[i][j] != BORDER){lo=i;co=j;}
    } fgetc(fin);
  }
  fclose(fin);
  for(int i=0; i<=n+1; i++){
    mat[i][0]=mat[i][m+1]=BORDER;
  }
  for(int i=0; i<=m+1; i++){
    mat[0][i]=mat[n+1][i]=BORDER;
  }
 
  int nr = 0;
  for(int i=1; i<=n; i++){
    for(int j=1; j<=m; j++){
      if(mat[i][j]=='C'){
        nr++;
        l = i; // :(
        c = j;
        fill_c();
      }
    }
  }
 
  int amax = 0;
  for(int i=1; i<=n; i++){
    for(int j=1; j<=m; j++){
      if(mat[i][j]=='P'){
        l = i; // :(
        c = j;
        int a = fill_p();
        if(a > amax)
          amax = a;
      }
    }
  }
 
  l = lo; // :(
  c = co;
  int p = fill_o();
 
 
  fout=fopen("oras.out", "w");
  fprintf(fout, "%d %d %d\n", p, nr, amax);
  fclose(fout);
  return 0;
}
