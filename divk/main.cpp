#include <stdio.h>

#define MAX(a, b) ((a)>(b)?(a):(b))
#define MAXN 1000001

int n, k;
long long sp[MAXN];
int main(){
  FILE *fin, *fout;
  fin = fopen("divk.in", "r");
  fscanf(fin, "%d%d", &n, &k);
  for(int i=0; i<n; i++){
    int val; fscanf(fin, "%d", &val);
    sp[i] = (i>0?sp[i-1]:0) + val;
  }
  fclose(fin);

  long long maxsum = 0;
  for(int i=0; i<k; i++){
    long long sum = 0;
    for(int j=i; j<n-k+1; j+=k){
      sum = MAX(sp[j+k-1]-(j>0?sp[j-1]:0), sum+sp[j+k-1]-(j>0?sp[j-1]:0));
      maxsum = MAX(maxsum, sum);
    }
  }

  fout = fopen("divk.out", "w");
  fprintf(fout, "%lld\n", maxsum);
  fclose(fout);
}
