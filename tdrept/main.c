// ONI 2014 8th grade
// __razv was here
#include <stdio.h>

#define MAXN 100003

typedef struct{
  int x;
  int y;
}point;

int n;

int fx[MAXN];
int fy[MAXN];
point v[MAXN];

int main(){
  FILE *fin, *fout;
  fin = fopen("tdrept.in", "r");
  fscanf(fin, "%d", &n);
  for(int i=0; i<n; i++){
    int x, y;
    fscanf(fin, "%d%d", &x, &y);
    fx[x]++;
    fy[y]++;
    v[i] = (point){x, y};
  }
  fclose(fin);

  long long total = 0;
  for(int i=0; i<n; i++){
    total+=((long long)fy[v[i].y]-1)*(fx[v[i].x]-1);
    total%=666013;
  }

  fout = fopen("tdrept.out", "w");
  fprintf(fout, "%lld", total);
  fclose(fout);
}
