#include <stdio.h>
#include <limits.h>

#define MAX(a, b)((a)>(b)?(a):(b))
#define MIN(a, b)((a)>(b)?(b):(a))

#define MAXN 100069
#define EOL -1

int n, k;
int v[MAXN];
long long secv[MAXN];
long long maxs[MAXN];
long long maxd[MAXN];

int main(){
  FILE *fin, *fout;
  fin = fopen("ks.in", "r");
  fscanf(fin, "%d%d", &n, &k);
  long long sum = 0;
  long long max = -1;
  for(int i=0; i<n; i++){
    fscanf(fin, "%d", &v[i]);
    sum = sum+v[i] - (i-k>=0?v[i-k]:0);
    if(i<k-1){
      secv[i] = -1;
    }
    else{
      secv[i] = sum;
    }
    max = MAX(max, secv[i]);
    maxs[i] = max;
  }
  max = -1;
  for(int i=n-1; i>=0; i--){
    max = MAX(max, secv[i]);
    maxd[i] = max; 
  }
  fclose(fin);

  long long min = LLONG_MAX;
  for(int i=0; i<n; i++){
    min = MIN(min, MAX((i>0?maxs[i-1]:0), (i+2*k-1<n?maxd[i+2*k-1]:0)));
  }

  fout = fopen("ks.out", "w");
  fprintf(fout, "%lld\n", min);
  fclose(fout);
  return 0;
}