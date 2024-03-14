#include <stdio.h>

#define ADD 1000
#define MAXN 1000

typedef struct{
  int x;
  int y;
}point;

int p, n;

int mat[MAXN][MAXN];
int line[MAXN][MAXN]
int connect[MAXN][MAXN];

int main(){
  FILE *fin, *fout;
  fin = fopen("z.in", "r");
  fscanf(fin, "%d %d", &p, &n);
  point last = {-__INT_MAX__-1, -__INT_MAX__-1};
  for(int i=1; i<=n; i++){
    point p;
    fscanf(fin, "%d%d", &p.x, &p.y);
    mat[p.y][p.x] = i;

  }
  fclose(fin);


  fout = fopen("z.out", "w");
  fclose(fout);
  return 0;
}
