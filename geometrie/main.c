#include <limits.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#define MAXN 2500
#define MAXCOORD 1000

int mat[MAXCOORD*4+1][MAXCOORD*4+1];

typedef struct{
  short x;
  short y;
}point;

point v[MAXN+1];int n;
point p;

void readPoint(point *p, FILE *fin){
  fscanf(fin, "%hd %hd\n", &p->x, &p->y);
}

void printPoint(point *p, FILE *fout){
  fprintf(fout, "%hd %hd\n", p->x, p->y);
}

double dist(point a, point b){
  double distance = sqrt((a.x-b.x)*(a.x-b.x)+(a.y-b.y)*(a.y-b.y));
  return distance;
}

int compPoints(point a, point b){
  if(a.x!=b.x) return (a.x>b.x)-(b.x>a.x);
  else return (a.y>b.y)-(b.y>a.y);
}

int main(){
  int c;
  FILE *fin, *fout;
  fin=fopen("geometrie.in", "r");
  fscanf(fin, "%d\n%d\n", &c, &n);
  for(int i=0; i<n; i++){
    readPoint(&v[i], fin);
  }
  readPoint(&p, fin);
  fclose(fin);

  for(int i=0; i<n; i++){
    for(int j=i+1; j<n; j++){
      mat[2000+v[i].x+v[j].x][2000+v[i].y+v[j].y]++;
    }
  }
 
  int total=0;
  for(int i=0; i<=4*MAXCOORD; i++){
    for(int j=0; j<=4*MAXCOORD; j++){
      int n = mat[i][j];
      total+=(n-1)*n/2;
    }
  }

  fout=fopen("geometrie.out", "w");
  if(c==1){
    double min=INT_MAX; int minp=0;
    for(int i=0; i<n; i++){
      double d = dist(v[i], p);
      if(d<min || (d==min && compPoints(v[i], v[minp])>0)){
        min = d;
        minp = i;
      }
    }
    printPoint(&v[minp], fout);
  }
  else{
    fprintf(fout, "%d\n", total);
  }
  fclose(fout);
  return EXIT_SUCCESS;
}
