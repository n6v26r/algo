#include <stdio.h>
#include <stdlib.h>

#define MAXN 1000000
#define MAXVAL MAXN

int p, n;
int ciur[MAXVAL+1];
int f[MAXVAL+1];

int main(){
  FILE *fin, *fout;
  fin = fopen("cufar.in", "r");
  fscanf(fin, "%d %d", &p, &n);
  for(int i=0; i<n; i++){
    int val, k;
    fscanf(fin, "%d %d", &val, &k);
    f[val] = k;
  }
  fclose(fin);

 long long sum = 0;

  for(int i=2; i<=MAXVAL; i++){
    if(!ciur[i])
      for(int d=i; d<=MAXVAL; d+=i){
        ciur[d]++;
        if(ciur[d] == f[d])
          sum+=i;
      }
  }
   
  fout = fopen("cufar.out", "w");
  fprintf(fout, "%lld\n", sum);
  fclose(fout);
  return 0;
}
