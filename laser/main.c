#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>

#define MAXN 5004
#define INF 1e18 

typedef struct{
  long long x1;
  long long x2;
  long long y1;
  long long y2;
  long long cost;
}seg;

seg v[MAXN+1];
long long dp[MAXN+1];

int cmp2(long long x1, long long y1, long long x2, long long y2){
  if(!y1 && !y2) return (x1*x2>0 || (x1<0 && x2>0));
  if(!y1) return x1 < 0;
  if(!y2) return x2 > 0;
  return x1*y2 <= y1*x2;
}

int cmp(long long x1, long long y1, long long x2, long long y2){
  if(!y1 && !y2) return x1 < x2;
  if(!y1) return x1 < 0;
  if(!y2) return x2 > 0;
  return x1*y2 < y1*x2;
}

int comp(const void* a, const void* b){
  seg _a = *((const seg*)a);
  seg _b = *((const seg*)b);

  return cmp(_b.x1, _b.y1, _a.x1, _a.y1);
}

int main(){
  int n;
  FILE *fin, *fout;
  fin=fopen("laser.in", "r");
  fscanf(fin, "%d", &n);
  for(int i=0; i<n; i++){
    fscanf(fin, "%lld %lld %lld %lld %lld", &v[i].x1, &v[i].y1, &v[i].x2, &v[i].y2, &v[i].cost);
    if(cmp(v[i].x2, v[i].y2, v[i].x1, v[i].y1)){
      int aux = v[i].x1;
      v[i].x1 = v[i].x2;
      v[i].x2 = aux;

      aux = v[i].y1;
      v[i].y1 = v[i].y2;
      v[i].y2 = aux;
    }
  }
  qsort(v, n, sizeof(seg), comp);
  fclose(fin);

  for(int i=0; i<n; i++){
    if(v[i].x1<0 && v[i].y1==0) dp[i] = v[i].cost;
    else{
      dp[i] = INF;
      for(int j=0; j<i; j++){
        if(cmp2(v[i].x1, v[i].y1, v[j].x2, v[j].y2))
          if(dp[i]>dp[j]+v[i].cost){
            dp[i] = dp[j] + v[i].cost;
          }
      }
    }
  }

  fout=fopen("laser.out", "w");
  long long min = INF;
  for(int i=0; i<n; i++){
    if(v[i].x2 > 0 && v[i].y2 == 0)
      if(min>dp[i]) min = dp[i];
  } 
  if(min==INF)
    fprintf(fout, "-1\n");
  else
   fprintf(fout, "%lld\n", min);
  fclose(fout);
  return 0;
}
