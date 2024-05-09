// ONI 2017 8th grade 
// NOTE: NOT fully correct
#include <stdio.h>
#include <system_error>
#include <vector>
#include <algorithm>

#define MAXN 1001
#define abs(a) ((a)>0?(a):-(a))

typedef struct{
  int x;
  int y;
}point;

typedef struct{
  point a;
  point b;
}seg;

int n, p;
point v[MAXN];

int cmmdc(int a, int b){
  while(b>0){
    int r = a%b;
    a = b;
    b = r;
  }
  return a;
}

std::vector<seg> segmente;

char mark [2*MAXN+10][2*MAXN+10];

bool eg(point a, point b){
  return a.x==b.x && a.y == b.y;
}

bool eq(point a, point b){
  if(a.x!=b.x) return a.x>b.x;
  return a.y>b.y;
}

bool cmp(point a, point b){
  if((a.x>b.x) && (a.y>b.y)) return 1;

  return 0;
}

double getSlope(seg s){
  point slope = (point){s.a.x-s.b.x, s.a.y-s.b.y};
  return (double)(slope.y)/(double)(slope.x);
}

bool compSeg(seg a, seg b){
  double pantaA = getSlope(a);
  double pantaB = getSlope(b);

  if(pantaA!=pantaB) return pantaA<pantaB;
  if(!eg(a.a, b.a)) return !eq(a.a, b.a);
  return !eq(a.b, b.b);
}

int testZ(point a, point b){
    int lina = a.y;
    int linb = b.y;
    int y;
    for(y = b.x; y<=a.x; y++){
      if(!mark[lina+MAXN][y+MAXN] || !mark[linb+MAXN][y+MAXN])
        break;
    }
    if(y>a.x) return 1;
    return 0;
}

int main(){
  FILE *fin, *fout;
  fin = fopen("z.in", "r");
  fscanf(fin, "%d%d", &p, &n);
  int pass0 = 0;
  for(int i=0; i<n; i++){
    fscanf(fin, "%d%d", &v[i].x, &v[i].y);
    if(i>=1){
      point a = v[i-1];
      point b = v[i];

      if(a.y == b.y){
        if(a.x>b.x){
          point aux = a;
          a = b;
          b = aux;
        }
        // printf("LINE: [%d %d] [%d %d]\n", a.x, a.y, b.x, b.y);
        for(int i = a.x; i<=b.x; i++){
          mark[a.y+MAXN][i+MAXN] = 1;
        }
      }
      else if(a.x!=b.x){
        if(!cmp(a, b)){
          point aux = a;
          a = b;
          b = aux;
        }
        if(cmp(a, b))
          segmente.push_back((seg){a, b});
      }

      if(((a.x<=0 && b.x>=0) || (a.x>=0 && b.x<=0)) &&
      ((a.y<=0 && b.y>=0) || (a.y>=0 && b.y<=0))){
        if((a.x ==0 && a.y ==0) || (b.x==0 && b.y==0)) continue;
        if((a.x == 0 && b.x ==0) || (a.y==0 && b.y==0)) {pass0++;}
        if(a.x == 0 || a.y ==0 || b.x ==0 || b.y ==0) continue;
        a = (point) {abs(a.x), abs(a.y)};
        b = (point) {abs(b.x), abs(b.y)};
        a = (point){a.x/cmmdc(a.x, a.y), a.y/cmmdc(a.x, a.y)};
        b = (point){b.x/cmmdc(b.x, b.y), b.y/cmmdc(b.x, b.y)};
        if(a.x == b.x && a.y == b.y) pass0++;
      }
    }
  }
  fclose(fin);

  std::sort(segmente.begin(), segmente.end(), compSeg);

  // printf("%d\n", segmente.size());
  // for(int i=0; i<segmente.size(); i++){
  //   printf("[%d %d] [%d %d] (%f)\n",
  //          segmente[i].a.x, segmente[i].a.y,
  //          segmente[i].b.x, segmente[i].b.y,
  //          getSlope(segmente[i]));
  // }

  int total = 0;
  for(int i=0; i<segmente.size(); i++){
    point a = segmente[i].a;
    point b = segmente[i].b;
    // printf("[%d %d] [%d %d]: %d\n", a.x, a.y, b.x, b.y, testZ(a, b));
    total+= testZ(a, b);
    for(int j=i+1; getSlope(segmente[j])==getSlope(segmente[i]); j++){
      if(!eg(segmente[j].a, segmente[i].b)) continue;
      b = segmente[j].b;
      total+=testZ(a, b);
    }
  }

  fout = fopen("z.out", "w");
  // for(int i=300; i<901; i++){
  //   for(int j=100; j<250; j++){
  //     fprintf(fout, "%d ", mark[i+MAXN][j+MAXN]);
  //   }
  //   fprintf(fout, "\n");
  // }

  if(p==2) fprintf(fout, "%d\n", total);
  else
    fprintf(fout,  "%d\n", pass0);
  fclose(fout);
  return 0;
}
<<<<<<< HEAD

=======
>>>>>>> abdbb5b5b4469998341d71fd297f22a83f9bacb1
