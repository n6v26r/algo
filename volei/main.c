#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX(a, b) ((a)>(b)?(a):(b))
#define MAXN 2001

int f[MAXN];
int b[MAXN];
char used[MAXN];
char buffer[1000000];
int n, m;

int compInt(const void* a, const void* b){
  int _a = *((const int*)a);
  int _b = *((const int*)b);

  return _a-_b;
}

int cautbin(int val){
  int s = -1;
  int d = m-1;
  while(d-s>1){
    int m = (s+d)/2;
    if(b[m]<val) s = m;
    else d = m;
  }
  return d;
}

int main(){
  FILE *fin, *fout;
  fin = fopen("volei.in", "r");
  fscanf(fin, "%d", &n);
  for(int i=0; i<n; i++) fscanf(fin, "%d", &f[i]);
  fscanf(fin, "%d", &m);
  for(int i=0; i<m; i++) fscanf(fin, "%d", &b[i]);
  fclose(fin);

  qsort(b, m, sizeof(int), compInt);

  fout = fopen("volei.out", "w");
  int total = 0;
  for(int i=0; i<n; i++){
    int val = MAX(f[i], f[(i+1)%n]);
    int minp = cautbin(val+1);
    while(used[minp] && minp<m) minp++;
    if(minp<m && b[minp]>val){
      sprintf(buffer+strlen(buffer), "%d (%d) ", f[i], b[minp]);
      used[minp] = 1;
      total++;
    }
    else sprintf(buffer+strlen(buffer), "%d ", f[i]);
  }
  fprintf(fout, "%d\n%s\n", total, buffer);
  fclose(fout);
  return 0;
}
