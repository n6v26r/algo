#include <stdio.h>
#include <stdlib.h>
#include <float.h>
#include <math.h>

#define MAXN 100000

typedef struct{
  double x;
  double y;
}point;

int n;

point v[MAXN];
point a[MAXN];

int compX(const void* a, const void* b){
  point _a = *((const point*)a);
  point _b = *((const point*)b);

  if(_a.x<_b.x) return -1;
  if(_a.x==_b.x) return 0;
  return 1;
}

int rev_compX(const void* a, const void* b){
  return -compX(a, b);
}

double dist(point a, point b){
  return sqrt((a.x-b.x)*(a.x-b.x)+(a.y-b.y)*(a.y-b.y));
}

int main(){
  FILE *fin, *fout;
  fin = fopen("bigcircle.in", "r");
  fscanf(fin, "%d", &n);
  point p = {FLT_MAX, FLT_MAX};
  for(int i=0; i<n; i++){
    fscanf(fin, "%lf %lf", &v[i].x, &v[i].y);
    if(v[i].x<p.x) p = v[i];
  }
  fclose(fin);

  int j = 0;
  for(int i=0; i<n; i++){
    if(v[i].y>=p.y){a[j++] = v[i];}
  }
  qsort(a, j, sizeof(point), compX);

  int size1 = j;
  for(int i=0; i<n; i++){
    if(v[i].y<p.y)a[j++] = v[i];
  }
  qsort(a+size1-1, j-size1+1, sizeof(point), rev_compX);

  double min = FLT_MAX;
  for(int i=0; i<n; i++){
    if(dist(a[i], a[(i+1)%n])<min){
      min = dist(a[i], a[(i+1)%n]);
    }
  }

  fout = fopen("bigcircle.out", "w");
  fprintf(fout, "%.2lf\n", min);
  fclose(fout);
  return 0;
}
