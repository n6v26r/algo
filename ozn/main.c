#include <stdio.h>
#include <ctype.h>
    
#define MAXCOORD 2000000
    
int v[MAXCOORD+1];
    
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
  int n, k;
  int a, b, nr;
  FILE *fin, *fout;
  fin=fopen("ozn.in", "r");
  fscanf(fin, "%d%d", &n, &k);
  for(int i=0; i<n; i++){
    readInt(&a, fin); readInt(&b, fin);
    readInt(&b, fin); readInt(&nr, fin);
    readInt(&nr, fin);
    v[a-1]+=nr;
    v[b]+=-nr;
  }
  for(int i=1; i<MAXCOORD; i++){
    v[i]+=v[i-1];
  }
  fout=fopen("ozn.out", "w");
  for(int i=0; i<k; i++){
    readInt(&a, fin);
    fprintf(fout, "%d\n", v[a-1]);
  }
  fclose(fin);
  fclose(fout);
  return 0;
}
