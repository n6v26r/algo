#include <iostream>
#include <stdio.h>
#include <string.h>

#define MAXN 501
#define TIME 55440
#define MAXT 20

int n, m, k;

int points[MAXN][MAXN];
int timp[MAXN][MAXN];

struct {int i;int j;} when[MAXT+1];

long long sum[TIME+2];

int main(){
  memset(when, -1, sizeof(when));
  FILE *fin, *fout;
  fin = fopen("iepurasi.in", "r");
  fscanf(fin, "%d%d%d", &n, &m, &k);
  for(int i=0; i<n; i++)
    for(int j=0; j<m; j++)
      fscanf(fin, "%d", &points[i][j]);
  for(int i=0; i<n; i++)
    for(int j=0; j<m; j++){
      fscanf(fin, "%d", &timp[i][j]);
      if(when[timp[i][j]].i==-1 || points[i][j]>points[when[timp[i][j]].i][when[timp[i][j]].j]){
        //printf("%d -> %d\n", timp[i][j], points[i][j]);
        when[timp[i][j]].i = i;
        when[timp[i][j]].j = j;
      }
    }
  fclose(fin);

  for(int i=1; i<=TIME; i++){
    int maxval = 0;
    int d = 1;
    while(d<=12){
      if(i%d==0 && points[when[d].i][when[d].j]>maxval) maxval = points[when[d].i][when[d].j];
      d++;
    }
    sum[i]=(i>0?sum[i-1]:0)+maxval;
  }

  long long total = (long long)k/TIME*(sum[TIME])+sum[k%TIME];

  fout = fopen("iepurasi.out", "w");
  fprintf(fout, "%lld\n", total);
  fclose(fout);
}
