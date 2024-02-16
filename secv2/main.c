#include <stdio.h>
#include <stdlib.h>

#define MAXN 50000

int v[MAXN+1];

int main(){
  int n, k;
  FILE *fin, *fout;
  fin = fopen("secv2.in", "r");
  fscanf(fin, "%d %d", &n, &k);
  for(int i=0; i<n; i++){
    fscanf(fin, "%d", &v[i]);
    v[i] += (i>0?v[i-1]:0);
  }
  fclose(fin);

  int s, d;
  int max=-__INT_MAX__, maxp=0;
  for(int i=k-1; i<n; i++){
    //printf("%d\n", v[i]);
    if(v[i]>max){
      max = v[i];
      maxp = i;
      d = maxp;
    }
  }
  max = -__INT_MAX__;
  for(int i=d; i>=k-1; i--){
    int sum = v[d]-v[i-k];
    if(sum>max){
      max = sum;
      maxp = i-k+1;
      s = i-k+1;
    }
  }

  fout = fopen("secv2.out", "w");
  fprintf(fout, "%d %d %d\n", s+1, d+1, v[d]-v[s-1]);
  fclose(fout);
  return 0;
}
