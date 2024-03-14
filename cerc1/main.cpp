// ONI 2012 LOT Juniori 1
// https://www.pbinfo.ro/probleme/708/cerc1
#include <iostream>
#include <algorithm>
#define MAXN 1001

#define MIN(a, b) ((a)<(b)?(a):(b))

int n, m, l, c;

typedef struct{
  char val;
  int distmin;
}_type;

_type mat[MAXN*MAXN+1];
int spar[MAXN*MAXN+1];

int dist(int x1, int y1, int x2, int y2){
  return (x1-x2)*(x1-x2)+(y1-y2)*(y1-y2);
}

bool comp(_type a, _type b){
  return a.distmin<b.distmin;
}

int main(){
  FILE *fin, *fout;
  fin = fopen("cerc1.in", "r");
  fscanf(fin, "%d%d%d%d\n", &n, &m, &l, &c);
  l = l*2-1;
  c = c*2-1;
  for(int i=0; i<n; i++){
    for(int j=0; j<m; j++){
      mat[i*m+j].val = fgetc(fin);
      mat[i*m+j].distmin = MIN( dist(j*2, i*2, c, l), MIN( dist(j*2, (i+1)*2, c, l),
                          MIN( dist((j+1)*2, i*2, c, l), MIN( dist((j+1)*2, (i+1)*2 , c, l),
                          MIN( dist(j*2+1, i*2, c, l), MIN( dist(j*2, i*2+1, c, l),
                          MIN( dist((j+1)*2, i*2+1, c, l), dist(j*2+1, (i+1)*2, c, l) )))))));
    }fgetc(fin);
  }
  fclose(fin);

  std::sort(mat, mat+n*m, comp);

  for(int i=0; i<n; i++){
    for(int j=0; j<m; j++){
      spar[i*m+j] = (i*m+j>0?spar[i*m+j-1]:0)+(mat[i*m+j].val=='0'?-1:1);
    }
  }

  int maxDif = -__INT_MAX__;
  for(int raza=1; raza<(m+n)*2; raza++){
    int r = raza*raza;
    int s = 0;
    int d = n*m;
    while(d-s>1){
      int m = (s+d)/2;
      if(mat[m].distmin>r) d = m;
      else s = m;
    }
    if(maxDif<spar[s]) maxDif = spar[s];
  }

  fout = fopen("cerc1.out", "w");
  fprintf(fout, "%d\n", maxDif);
  fclose(fout);
  return 0;
}
