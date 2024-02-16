#include <stdio.h>

#define MOD 666013
#define MAXN 100001

typedef struct{
  int x;
  int y;
}point;

int n;

int xSame[MAXN];
int ySame[MAXN];
point v[MAXN];


int main(){
  FILE *fin, *fout;
  fin = fopen("tdrept.in", "r");
  fscanf(fin, "%d", &n);
  for(int i=0; i<n; i++){
    fscanf(fin, "%d%d", &v[i].x, &v[i].y);
    xSame[v[i].x]++;
    ySame[v[i].y]++;
  }
  fclose(fin);

  int total = 0;
  for(int i=0; i<n; i++){
    point p = v[i];
    total = (total + ((long long)(xSame[p.x]-1)%MOD)*((ySame[p.y]-1)%MOD)%MOD)%MOD;
  }

  fout = fopen("tdrept.out", "w");
  fprintf(fout, "%d\n", total%MOD);
  fclose(fout);
  return 0;
}
