#include <stdio.h>
#include <stdlib.h>

#define MAXSIZE 100000

int n, p;
long long k;
int v[MAXSIZE+1];

int compInt(const void* a, const void*  b){
  int _a = *((const int*)a);
  int _b = *((const int*)b);

  return _a-_b;
}

long long necesar(int h, int p){
  long long total = 0;
  long long buget = 0;
  for(int i=n-1; (p==1)?i>(n-1)/2-1:i>=0; i--){
    if(h>=v[i]){
      if(buget>(long long)h-v[i]){
        total += h-v[i];
        buget -= h-v[i];
      }
      else return __INT64_MAX__;
    }
    else
      buget += v[i]-h;
  }
  return total;
}

int find(long long k, int s, int d, int p){
  int m;
  while(d-s>1){
     m = (s+d)/2;
     if(necesar(m, p)>k){
       d = m;
     }
     else
       s = m;
  }
  return s;
}

int main(){
  int max = 0;
  FILE *fin, *fout;
  fin=fopen("uniform.in", "r");
  fscanf(fin, "%d\n%d %lld\n", &p, &n, &k);
  for(int i=0; i<n; i++){
    fscanf(fin, "%d ", &v[i]);
    if(v[i]>max)
      max = v[i];
  }
  fclose(fin);

  int optim=0;
  qsort(v, n, sizeof(int), compInt);
  optim = find(k, 0, max+1, p);

  fout=fopen("uniform.out", "w");
  fprintf(fout, "%d %lld\n", optim, necesar(optim, p));
  fclose(fout);
  return 0;
}
