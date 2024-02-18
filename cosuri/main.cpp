#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <algorithm>

#define MAXN 1000001

int t, n;

int v[MAXN];

int compInt(const void* a, const void* b){
  int _a = *((const int*)a);
  int _b = *((const int*)b);

  return _a-_b;
}

int main(){
  FILE *fin, *fout;
  fin = fopen("cosuri.in", "r");
  fscanf(fin, "%d%d", &t, &n);
  for(int i=0; i<2*n; i++){
    fscanf(fin, "%d", &v[i]);
  }
  fclose(fin);

  //qsort(v, 2*n, sizeof(int), compInt);
  std::sort(v, v+2*n);

  int j = 0;
  int i = 2*n-1;
  int min = INT_MAX;
  int sum = v[0]+v[2*n-1];
  while(j<i){
    if(v[i]-v[j]<min) min = v[i]-v[j];
    if(v[i]+v[j]!=sum) break;
    i--;
    j++;
  }

  fout = fopen("cosuri.out", "w");
  if(t==1){
    fprintf(fout, "%d %d\n", v[0]+v[1], v[2*n-1]+v[2*n-2]);
  }
  else{
    if(i<j) fprintf(fout, "DA\n%d\n", min);
    else fprintf(fout, "NU");
  }
  fclose(fout);
  return 0;
}