#include <stdio.h>

#define MAXN 11100001

long long supersum(int n){
  long long sum=0;
  for(int d=1; d*d<=n; d++){
    sum+=d;
    if(d*d<n){
      sum+=(long long)d*(n/d-d)+(long long)((d+1)+(n/d))*(n/d-d)/2;
    }
  }
  return sum;
}

long long k;

int main(){
  FILE *fin, *fout; 
  fin = fopen("supersuma.in", "r");
  fscanf(fin, "%lld", &k);
  fclose(fin);

  int s = 0;
  int d = MAXN;
  while(d-s>1){
    int m = (s+d)/2;
    if(supersum(m)<k)
      s = m;
    else d = m;
  }

  fout = fopen("supersuma.out", "w");
  fprintf(fout, "%d\n", d);
  fclose(fout);
  return 0;
}
