#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define MAXN 50000

int v[MAXN];
int h[MAXN];

int main(){
  int c, n, val, pos;
  FILE *fin, *fout;
  fin = fopen("rafturi.in", "r");
  fscanf(fin, "%d%d", &c, &n);
  for(int i=0; i<n; i++){
    fscanf(fin, "%d%d", &pos, &val);
    if(v[pos]<val)
      v[pos]=val;
  }
  fclose(fin);

  for(int i=1; i<=c; i++){
    h[i] = INT_MAX;
    int lvl = 0;
    for(int j=i; j>i-3 && j>0; j--){
      if(v[j]>lvl) lvl = v[j];
      if(h[j-1]+lvl<h[i])
        h[i] = h[j-1]+lvl;
    }
  }

  fout = fopen("rafturi.out", "w");
  fprintf(fout, "%d\n", h[c]);
  fclose(fout);
  return EXIT_SUCCESS;
}
