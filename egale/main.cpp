// PreOJI 2024 8th grade
// https://kilonova.ro/problems/2409/
#include <iostream>

#define MAXN 100001
#define MAX(a, b) ((a)>(b)?(a):(b))
#define MIN(a, b) ((a)<(b)?(a):(b))

int n, q;
int rmq[30][MAXN];
int lg[MAXN];
int spar[MAXN];

int getmax(int i, int j){
  int len = j-i+1;
  int k = lg[len];
  return MAX( rmq[k][i], rmq[k][j-(1<<k)+1]);
}

int main(){
  FILE *fin, *fout;
  fin = fopen("egale.in", "r");
  fscanf(fin, "%d%d", &n, &q);
  for(int i=0; i<n; i++){
    fscanf(fin, "%d", &rmq[0][i]);
    spar[i] = (i>0?spar[i-1]:0) + (i>0 && rmq[0][i-1]>rmq[0][i]?rmq[0][i-1]-rmq[0][i]:0);
    if(i>=2) lg[i] = lg[i/2] + 1;
  } lg[n] = lg[n/2] + 1;
  fout = fopen("egale.out", "w");
  for(int i = 1; i<=lg[n]; i++){
    for(int j=0; j+(1<<(i-1))<n; j++){
      rmq[i][j] = MAX(rmq[i-1][j], rmq[i-1][j+(1<<(i-1))] );
    }
  }

  while(q>0){
    int l, r, v; fscanf(fin, "%d %d %d", &l, &r, &v); l--; r--;
    if(getmax(l, r)>v) fprintf(fout, "%d\n", v+1);
    else{
      fprintf(fout, "%d\n", MIN(spar[r]-spar[l]+v-rmq[0][l], v+1));
    }
    q--;
  }

  fclose(fin);
  fclose(fout);
}
