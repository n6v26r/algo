#include <stdio.h>
#include <stdlib.h>

#define MAXN 100001

int n;
int v[MAXN];
int f[MAXN];

int compInt(const void* a, const void* b){
  int _a = *((const int*)a);
  int _b = *((const int*)b);

  return _a-_b;
}

int main(){
  FILE *fin, *fout;
  fin = fopen("deal.in", "r");
  fscanf(fin, "%d\n", &n);
  int maj = -1;
  int max = 0;
  for(int i=0; i<n; i++){
    fscanf(fin, "%d", &v[i]);
    f[v[i]]++;
    if(f[v[i]]>=(n+1)/2) maj = v[i];
    if(v[i]>max) max = v[i];
  }
  fclose(fin);

  long long sum = 0;
  qsort(v, n, sizeof(int), compInt);

  if(max==maj){sum = ((long long)n-f[maj])*max; if(2*f[maj]-n>1)sum+=max;}
  else if(maj>=0){
    int i;
    for(i=n-1; v[i]>maj; i--){
      sum+=v[i];
      f[maj]--;
    }
    while(i>=0 && v[i]==maj)i--;
    char sml = 0;
    if(i>=0) sml = 1;
    while(i>=0){
      sum+=maj;
      f[maj]--;
      i--;
    }
    if(sml && f[maj]>=2) sum+=maj;
  }
  else{
    for(int i=n-1; i>((n-1)/2); i--) sum+=v[i];
  }

  fout = fopen("deal.out", "w");
  fprintf(fout, "%lld\n", sum);
  fclose(fout);
  return 0;
}
