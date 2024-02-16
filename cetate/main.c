#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXN 400
#define MAX(a, b) ((a)>(b)?(a):(b))
#define MIN(a, b) ((a)<(b)?(a):(b))

long long mat[MAXN+1][MAXN+1];
int p, n, m, k;

long long aib[MAXN+69];

void update(int i, long long val){
  while(i<=m){
    aib[i] = MAX(aib[i], val);
    i += (i&(-i));
  }
}

long long g(int i){
  int ans;
  do{
    i -= (i&(-i));
    ans = MAX(aib[i], ans);
  }while(i>0);
  return ans;
}

long long get(int i, int j, int lin, int col){
  return mat[lin][col]-(j>0?mat[lin][j-1]:0)-(i>0?mat[i-1][col]:0)+(i>0&&j>0?mat[i-1][j-1]:0);
}

void getBest(FILE* fout){
  long long max=-__LONG_LONG_MAX__;
  int maxi, maxj;
  for(int i=0; i<=n-k; i++){
    for(int j=0; j<=m-k; j++){
      long long val = get(i, j, i+k-1, j+k-1);
      if(val>max){
        max = val;
        maxi = i+1;
        maxj = j+1;
      }
    }
  }
  fprintf(fout, "%lld\n%d %d %d %d\n", max, maxi, maxj, maxi+k-1, maxj+k-1);
}

void getBestK(FILE* fout){
  long long bestmax = 0;
  int besti, bestj, bestlin, bestcol;
  for(int ck=1; ck<=k; ck++){
    for(int j=0; j<=n-ck; j++){
      int a = j, b = j+ck-1; // []
      memset(aib, -128, sizeof aib);
      printf("Calculating for: %d %d : \n", a, b);
      for(int i=m-1; i>=0; i--){
        int val = get(a, i-k+1, b, i);
        printf("%d\n\n", val);
        update(i+1, val);
        long long w = g(MIN(i+k-1, m-1)+1)-get(a, i-k, b, i-1);
        printf("%d -> %lld\n", MIN(i+k-1, m-1)+1, w);
        for(int i=1; i<=m; i++){
          printf("%lld ", g(i)-g(i-1));
          // printf("%lld ", aib[i]);
        }printf("\n");
      }
     // printf("-> %d\n", max);
      // if(max>bestmax){
      //   bestmax = max;
      //   besti = a+1;
      //   bestj = s+1;
      //   bestlin = b+1;
      //   bestcol = d+1;
      // }
    }
  }
  fprintf(fout, "%lld\n%d %d %d %d\n", bestmax, besti, bestj, bestlin, bestcol);
}

int main(){
  FILE *fin, *fout;
  fin=fopen("cetate.in", "r");
  fscanf(fin, "%d %d %d %d\n", &p, &n, &m, &k);
  for(int i=0; i<n; i++){
    for(int j=0; j<m; j++){
      fscanf(fin, "%lld", &mat[i][j]);
      mat[i][j] = mat[i][j]+(i>0?mat[i-1][j]:0)+(j>0?mat[i][j-1]:0)-(i>0&&j>0?mat[i-1][j-1]:0);
    }
  }
  fclose(fin);
    
  fout=fopen("cetate.out", "w");
  if(p==1) getBest(fout);
  else getBestK(fout);
  fclose(fout);
}
