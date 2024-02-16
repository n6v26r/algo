#include <stdio.h>
#include <ctype.h>
#include <string.h>
 
#define MAXN 10000
#define MAXZ MAXN
#define NIL -1
 
int col[MAXZ+1], next[MAXZ+1], lin[MAXN+1];
int sumpar[MAXN+1], v[MAXN];
int stack[MAXN+1], sp=-1;
 
int n, m, z;
 
 
void readInt(int *n, FILE *fin){
  char c = fgetc(fin);
  *n = 0;
  while(!isdigit(c))
    c=fgetc(fin);
  while(isdigit(c)){
    *n = (*n)*10+c-'0';
    c=fgetc(fin);
  }
 
}
	
int main(){
  memset(lin, NIL, sizeof lin);
  FILE *fin, *fout;
  fin=fopen("dreptunghi1.in", "r");
  fscanf(fin, "%d%d%d\n", &n, &m, &z);
  for(int i=0; i<z; i++){
    int l, c;
    readInt(&l, fin);
    readInt(&c, fin);
    l--;
    c--;
    col[i]=c;
 
    next[i]=lin[l];
    lin[l]=i;
  }
  fclose(fin);
 
 
  int max=0;
  for(int i=0; i<n; i++){
    int c = lin[i];
    while(c>NIL){
      sumpar[col[c]] = -1;
      c=next[c];
    }
 
    for(int j=0; j<m; j++){
      sumpar[j]++;
      v[j]=1;
      while(sp>-1 && sumpar[stack[sp]]>=sumpar[j]){v[j]+=v[stack[sp]]; sp--;}
      stack[++sp]=j;
    }
 
    sp=-1;
    for(int j=m-1; j>=0; j--){
      int sv = 0;
      while(sp>-1 && sumpar[stack[sp]]>=sumpar[j]){sv+=v[stack[sp]]; sp--;}
      stack[++sp]=j;
 
      v[j]+=sv;
      if(sumpar[j]*(v[j]) > max){
        max = sumpar[j]*(v[j]);
      }
 
      v[j]=sv+1;
    }
 
    sp=-1;
  }
 
  fout=fopen("dreptunghi1.out", "w");
  fprintf(fout, "%d\n", max);
  fclose(fout);
}
