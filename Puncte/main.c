#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#define MAX(a, b) ((a)>(b)?(a):(b))

#define MAXN 250000
#define MAXCOORD 1000

typedef struct{
  int x;
  int y;
}point;

point v[MAXN+1];
int next[MAXN+1];
bool fill[MAXN+1];
int Xsame[2*MAXCOORD+7];
int Ysame[2*MAXCOORD+7];

int n;

int compPoint(const void *a, const void *b){
  point _a = *((const point*)a);
  point _b = *((const point*)b);

  if(_a.x!=_b.x) return _a.x-_b.x;
  return _a.y-_b.y;
}

int main(){
  FILE *fin, *fout;
  fin = fopen("puncte.in", "r");
  fscanf(fin, "%d\n", &n);
  int max = 0;
  bool has00 = false;
  for(int i=0; i<n; i++){
    fscanf(fin, "%d %d\n", &v[i].x, &v[i].y);
    if(v[i].x==v[i].y && v[i].x==0) has00 = true;
    Xsame[MAXCOORD+v[i].x]++;
    Ysame[MAXCOORD+v[i].y]++;
    max = MAX(max, MAX(Xsame[MAXCOORD+v[i].x], Ysame[MAXCOORD+v[i].y]));
  } 
  fclose(fin);
  
  int a = 0;
  int b = 0;

  for(int i=0; i<n; i++){
    if(v[i].x == v[i].y)
      a++;
    if(v[i].x == -v[i].y)
      b++;
  }

  int rasp2 = (!has00?(a*b):(a-1)*(b-1))+(b>1)+(a>1);

  qsort(v, n, sizeof(point), compPoint);
  for(int i=0; i<n; i++){
    if(i>0)next[i-1] = i;
  }
  next[n-1] = 0;
  int i = n-1;
  while(next[i]!=i){
    next[i] = next[next[i]];
    i = next[next[i]];
  }

  fout = fopen("puncte.out", "w");
  fprintf(fout, "%d\n%d\n%d\n", max, rasp2, v[i].x);
  fclose(fout);
}
