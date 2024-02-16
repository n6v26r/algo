#include <stdio.h>

#define MAXVAL 1001
#define MAXN MAXVAL

typedef struct{
  int x;
  int y;
  int c;
}point;

int n, c;
int mat[2*MAXVAL][2*MAXVAL];
point v[MAXN];


int main(){
  FILE *fin, *fout;
  fin = fopen("dreptc.in", "r");
  fscanf(fin, "%d%d", &n, &c);
  for(int i=0; i<n; i++){
    fscanf(fin, "%d%d%d", &v[i].x, &v[i].y, &v[i].c);
    v[i].y+=MAXVAL;
    v[i].x+=MAXVAL;
    mat[v[i].y][v[i].x] = v[i].c;
  }
  fclose(fin);

  int total = 0;
  for(int i=0; i<n; i++){
    for(int j=i; j<n; j++){
      if(v[i].x==v[j].x || v[i].y == v[j].y) continue;
      if(mat[v[i].y][v[i].x] == mat[v[j].y][v[j].x] && 
        mat[v[i].y][v[i].x] == mat[v[i].y][v[j].x] &&
        mat[v[i].y][v[i].x] == mat[v[j].y][v[i].x]){
        
        total++;
      }
    }
  }

  fout = fopen("dreptc.out", "w");
  fprintf(fout, "%d\n", total/2);
  fclose(fout);
  return 0;
}
