#include <stdio.h>

#define MAXN 32382

int n;
int ciur[MAXN];
int prime[MAXN], size;

int divprimi[MAXN], k;

int main(){
  for(int i=2; i<MAXN; i++){
    if(!ciur[i]){
      for(int d=i; d<MAXN; d+=i)
        ciur[d] = 1;
      prime[size++] = i;
    }
  }
  printf("size: %d\n", size);
  FILE *fin, *fout;
  fin = fopen("cicada.in", "r");
  fscanf(fin, "%d", &n);
  fclose(fin);
  
  int i = 0;
  int d = prime[i];
  int m = n;
  while (d*d<=m){
    if(!(m%d)) divprimi[k++] = d;
    while(!(m%d)) m/=d;
    d = prime[++i];
  }
  if(m>1)
    divprimi[k++] = m;

  long long sum = 0;
  for(int i=0; i<k; i++){
    long long d = divprimi[i];
    sum += d*((n/d-1)*(n/d)/2);
  }

  for(int i=0; i<k; i++){
    for(int j=i+1; j<k; j++){
      long long x = divprimi[i];
      while (x*divprimi[j]<n)
        sum-=x*divprimi[j], x*=divprimi[i];
    }
  }

  fout = fopen("cicada.out", "w");
  fprintf(fout, "%lld\n", sum);
  fclose(fout);
}
