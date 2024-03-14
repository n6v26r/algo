#include <stdio.h>
#include <stdlib.h>

#define MAXN 1001
#define DIR 4
#define ABS(a) ((a)>0?(a):-(a))

char mat[MAXN][MAXN];
int n, m, p;

short int ansl[500000]; int sizel;
short int ansc[500000]; int sizec;

int dirLin[DIR] = {-1, 0, 1, 0};
int dirCol[DIR] = {0, 1, 0, -1};

int comp(const void *a, const void *b){
  short int _a = *((const short int*)a);
  short int _b = *((const short int*)b);

  return _a>_b;
}

int main(){
  FILE *fin, *fout;
  fin = fopen("boats.in", "r");
  fscanf(fin, "%d%d%d\n", &p, &n, &m);
  for(int i=0; i<n; i++){
    for(int j=0; j<m; j++){
      fscanf(fin, "%c ", &mat[i][j]);
      mat[i][j]-='0';
    }
  }
  fclose(fin);

  int barcute = 0;

  for(int i=0; i<n; i++){
    for(int j=0; j<m; j++){
      if(mat[i][j]!=1) continue;
      int dir = -1;
      for(int d = 0; d<DIR; d++){
        if(i+dirLin[d]<n && j+dirCol[d]<m && mat[i+dirLin[d]][j+dirCol[d]] == 1) dir = d;
      }

      if(dir==-1){
        barcute++;
      }
      else{
        short lin = 0;
        short col = 0;
        int _i = i;
        int _j = j;
        while(_i<n && _j<m && mat[_i][_j] == 1){
          mat[_i][_j] = 0;
          _i+=dirLin[dir]; lin+=ABS(dirLin[dir]);
          _j+=dirCol[dir]; col+=ABS(dirCol[dir]);
        }
        if(!(dir%2)) ansl[sizel++] = lin;
        else ansc[sizec++] = col;
      }
    }
  }

  qsort(ansl, sizel, sizeof(short int), comp);
  qsort(ansc, sizec, sizeof(short int), comp);
  fout = fopen("boats.out", "w");
  if(p==1){
    fprintf(fout, "%d\n", barcute);
    fclose(fout);
    return 0;
  }
  for(int i=0; i<sizec; i++){
    int eg = 1;
    while(i<sizec && ansc[i]==ansc[i+1]) i++, eg++;
    fprintf(fout, "L %hi %d\n", ansc[i], eg);
  }
  for(int i=0; i<sizel; i++){
    int eg = 1;
    while(i<sizel && ansl[i]==ansl[i+1]) i++, eg++;
    fprintf(fout, "C %hi %d\n", ansl[i], eg);
  }
  fclose(fout);
  return 0;
}
