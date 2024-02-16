#include <cstdio>
using namespace std;

#define MAXK 2001
#define MAXN 1001

typedef struct{
  int x;
  int y;
}point;

int n, m, k;
point start;

point v[MAXK];

unsigned char mat[MAXN][MAXN];

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

int main(){
  FILE *fin, *fout;
  fin = fopen("turist.in", "r");
  fscanf(fin, "%d%d\n%d%d\n%d", &n, &m, &start.x, &start.y, &k);
  for(int i=0; i<k; i++){
    fscanf(fin, "%d%d", &v[i].x, &v[i].y);
    mat[v[i].y][v[i].x] = 1;
  }
  fclose(fin);
  int _max = 0;
  for(int i=0; i<k; i++){
    point dif = {v[i].x-start.x, v[i].y-start.y};
    int _cmmdc = cmmdc(abs(dif.x), abs(dif.y));
    dif.x /= _cmmdc;
    dif.y /= _cmmdc;
    
    int lin = start.y;
    int col = start.x;
    int total = 0;
    while(lin>=0 && col>=0 && lin<=n && col<=m){
      total += mat[lin][col];
      lin+=dif.y;
      col+=dif.x;
      printf("%d %d\n", lin, col); fflush(stdout);
    }
    printf("%d %d %d\n", v[i].x, v[i].y, total); fflush(stdout);
    if(total>_max)_max = total;
  }

  fout = fopen("turist.out", "w");
  fprintf(fout, "%d\n", _max);
  fclose(fout);
  return 0;
}
