#include <stdio.h>
#include <stdlib.h>

#define MAXN 1001

int n, k, p;

int v[MAXN];
int gaps[MAXN], gCnt;

int compInt(const void* a, const void *b){
  int _a = *((const int*)a);
  int _b = *((const int*)b);

  return _a-_b;
}

int main(){
  FILE *fin, *fout;
  fin = fopen("afise.in", "r");
  fscanf(fin, "%d%d%d", &n, &k, &p);
  for(int i=0; i<k; i++) fscanf(fin, "%d", &v[i]);
  fclose(fin);
 
  qsort(v, k, sizeof(int), compInt);
  
  int last = -1;
  int panels = 1;
  for(int i=0; i<n; i++){
    if(last>-1 && v[i]-last>1){
      gaps[gCnt++] = v[i]-last-1;
      panels++;
    }
    last = v[i];
  }

  qsort(gaps, gCnt, sizeof(int), compInt);

  int i = 0;
  int len = k;
  while(panels>p){
    len+=gaps[i++];
    panels--;
  }

  fout = fopen("afise.out", "w");
  fprintf(fout, "%d %d\n", len, panels);
  fclose(fout);
  return 0;
}
