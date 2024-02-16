#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXN 400
#define MIN(a, b) ((a)<(b)?(a):(b))
#define MAX(a, b) ((a)>(b)?(a):(b))

long long mat[MAXN+1][MAXN+1];
int p, n, m, k;
long long aib[MAXN+3];

void update(int i, long long val){
  while(i<=n){
    aib[i] = MAX(aib[i], val);
    i += (i&-i);
  }
}

long long g(int i){
  int ans = 0;
  while(i>0){
    ans = MAX(aib[i], ans);
    i -= (i&-i);
  }
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
      memset(aib, 0x80, sizeof(aib));
      int a = j, b = j+ck-1; // []
      // printf("Calculating for: %d %d : \n", a, b);
      // int i=0;
      // while(i<k){
      //   while(q.u!=q.p && get(a, q.v[q.p]-k+1, b, q.v[q.p])<get(a, i-k+1, b, i)) q.p--;
      //   q.v[++q.p] = i
      // }
      printf("%d %d\n", a, b);
      int s, d;
      long long max=-__LONG_LONG_MAX__;
      int maxp;
      for(int i=m-1; i>=0; i--){
        printf(": %d %d -> %lld\n", i-k+1, i,  get(a, i-k+1, b, i));
        update(i+1, get(a, i-k+1, b, i));
        int val = g(MIN(i+k-1, m-1)+1);
        printf("(%d ) %d\n", MIN(i+k-1, m-1)+1,  val);

        if(val>max){
          max = val;
        }
      }
     /* d = maxp;
      if(max>bestmax){
        bestmax = max;
        besti = a+1;
        bestj = s+1;
        bestlin = b+1;
        bestcol = d+1;
      } */
    }
      // printf("-> %d\n", max);
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
