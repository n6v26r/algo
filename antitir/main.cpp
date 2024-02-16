#include <algorithm>
#include <stdio.h>
#include <ctype.h>

#define MAXN 1000000
#define abs(a) (((a)>=0)?(a):(-(a)))

typedef struct{
  int x;
  int y;
}point;

int n;

int vx[MAXN+1];
int vy[MAXN+1];

void readInt(int* n, FILE *fin){
  *n = 0;
  char c = fgetc(fin);
  while(isspace(c)) c = fgetc(fin);
  int semn = 1;
  if(c=='-') semn = -1, c=fgetc(fin);
  while(!isspace(c)){
    (*n) = (*n)*10+semn*(c-'0');
    c = fgetc(fin);
  }
}

int main(){
  FILE *fin, *fout;
  fin = fopen("antitir.in", "r");
  fscanf(fin, "%d", &n);
  for(int i=0; i<n; i++){
    point p;
    readInt(&p.x, fin);
    readInt(&p.y, fin);
    vx[i] = p.x;
    vy[i] = p.y;
  }
  fclose(fin);

  std::nth_element(vx, vx+n/2, vx+n);
  std::nth_element(vy, vy+n/2, vy+n);
  int xmed = vx[n/2];
  int ymed = vy[n/2];

  fout = fopen("antitir.out", "w");
  long long total = 0;
  for(int i=0; i<n; i++){
    total += (long long)abs(xmed-vx[i])+abs(ymed-vy[i]);
  }
  fprintf(fout,"%lld\n",total);
  fclose(fout);
  return 0;
}
