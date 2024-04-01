// ONI 2019 8th grade
// __razv was here
#include <stdio.h>
#include <string.h>

#define MAXN 110

int c, t, n;

typedef struct{
  long long x;
  long long y;
}point;

typedef struct{
  point a;
  point b;
}seg;

seg segment[MAXN];
point points[MAXN];

int upDown = 0;

void newPoint(int val, int i){
  if(upDown)points[i+1] = (point){points[i].x, points[i].y+val};
  else points[i+1] = (point){points[i].x+val, points[i].y};
  upDown = !upDown;
}

int order(point a, point b, point c){
  long long r = a.x*b.y-b.x*a.y + b.x*c.y-c.x*b.y + c.x*a.y-a.x*c.y;
  if(r==0) return 0;
  if(r<0) return -1;
  return 1;
}

char intersect(seg a, seg b){
  int r1 = order(a.a, a.b, b.a);
  int r2 = order(a.a, a.b, b.b);
  int r3 = order(b.a, b.b, a.a);
  int r4 = order(b.a, b.b, a.b);

  if(r1!=r2 && r3!=r4) return 1;
  return 0;
}

long long area(){
  long long surface = 0;
  for(int i=1; i<=n; i++){
    surface += points[i].x*points[i-1].y-points[i-1].x*points[i].y;
  }
  surface/=2;
  return surface>0?surface:-surface;
}

int main(){
  FILE *fin, *fout;
  fin = fopen("drept.in", "r");
  fout = fopen("drept.out", "w");
  fscanf(fin, "%d%d", &c, &t);
  while(t){
    fscanf(fin, "%d", &n);
    int val;
    points[0] = (point){0, 0};
    for(int i=0; i<n; i++){
      fscanf(fin, "%d", &val);
      newPoint(val, i);
      segment[i] = (seg){points[i], points[i+1]};
    }
    if(c==1){
      if(!(points[n].x==points[0].x && points[0].y==points[n].y)) {fprintf(fout, "0 "); t--; continue;}
      int i;
      for(i=0; i<n; i++){
        int j;
        for(j=0; j<i-1; j++){
          if(i==n-1 && j==0 ) continue;
          if(intersect(segment[i], segment[j])) break;
        }
        if(j<i-1) break;
      }
      if(i<n){fprintf(fout, "0 "); t--; continue;}

      fprintf(fout, "1 ");
    }
    else{
      fprintf(fout, "%lld ", area());
    }
    t--;
  }
  fprintf(fout, "\n");

  fclose(fin);
  fclose(fout);
}
