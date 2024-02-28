// OJI 2008 - 8th grade
// https://www.nerdarena.ro/problema/turist
// __razv vas here
#pragma GCC optimize("Ofast,fast-math,unroll-loops")
 
#include <ctype.h>
#include <stdio.h>
 
#define MAXK 2001
#define MAXN 1001
 
typedef struct{
  int x;
  int y;
}point;
 
int n, m, k;
point start;
 
point v[MAXK];
 
int cmmdc(int a, int b){
  while(b>0){
    int r = a%b;
    a = b;
    b = r;
  }
  return a;
}
 
inline int abs(int a){
  return (a>0?a:-a);
}
 
void readInt(int *n, FILE* fin){
  *n = 0;
  char c = fgetc(fin);
  while(!isdigit(c)) c = fgetc(fin);
  while(isdigit(c)) {(*n)=(*n)*10+c-'0'; c = fgetc(fin);}
}

int order(point a, point b, point c){
  return (a.x*b.y-a.y*b.x)+(b.x*c.y-b.y*c.x)+(c.x*a.y-c.y*a.x);
}

int same_direction(point origin, point a, point b){
  return ( ( (a.x>=origin.x && b.x>=origin.x) || (a.x<=origin.x && b.x<=origin.x) ) && ( (a.y>=origin.y && b.y>=origin.y) || (a.y<=origin.y && b.y<=origin.y) ) );
}

int main(){
  FILE *fin, *fout;
  fin = fopen("turist.in", "r");
  fscanf(fin, "%d%d\n%d%d\n%d", &n, &m, &start.x, &start.y, &k);
  for(int i=0; i<k; i++){
    readInt(&v[i].x, fin);
    readInt(&v[i].y, fin);
  }
  fclose(fin);
  int _max = 0;
  for(int i=0; i<k; i++){
    int total = 0;
    for(int j=0; j<k; j++){
      if(order(start, v[i], v[j])==0 && same_direction(start, v[i], v[j]))
        total++;
    }
 
    if(total>_max) _max = total;
  }
 
  fout = fopen("turist.out", "w");
  fprintf(fout, "%d\n", _max);
  fclose(fout);
  return 0;
}
