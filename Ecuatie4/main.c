// fortza bruta

#include <stdio.h>

int k;
long long n;

long long total = 0;

void d(long long n, int p){
  if(n==1){ total++; return;}
  if(p==0){
    return;
  }
  long long i;
  for(i=1; i*i<n; i++){
    if(n%i==0){d(n/i, p-1); d(i, p-1);}
  }
  if(i*i==n) d(i, p-1);
}

int main(){
  FILE *fin, *fout;
  fin = fopen("ecuatie4.in", "r");
  fscanf(fin, "%d %lld", &k, &n);
  fclose(fin);

  d(n, k);

  fout = fopen("ecuatie4.out", "w");
  fprintf(fout, "%lld\n", total);
  fclose(fout);
  return 0;
}
