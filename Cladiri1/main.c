#include <stdio.h>

#define MAX(a, b) ((a)>(b)?(a):(b))

#define MAXVAL 100001

typedef struct{
  int x;
  int y;
  int val;
}point;

inline int abs(int x){
  return x>0?0:1;
}

int f[MAXVAL];
int lvls[MAXVAL], lvlsize;

int main(){
  point center;
  point cladire;
  FILE *fin, *fout;
  fin = fopen("cladiri.in", "r");
  int total = 0;
  fscanf(fin, "%d %d %d\n", &center.x, &center.y, &center.val); 
  for(int i=0; fscanf(fin, "%d %d %d", &cladire.x, &cladire.y, &cladire.val); i++){ 
    int dist = MAX(abs(cladire.x-center.x), abs(cladire.y-center.y));
    if(center.val-dist>=cladire.val){
      total++;
      f[dist]++;
    }
    fgetc(fin);
    char c = fgetc(fin);
    if(c==EOF) break;
    else ungetc(c, fin);
  }
  fclose(fin);

  fout = fopen("cladiri.out", "w");
  fprintf(fout, "%d\n", total);
  int max = 0;
  for(int i=0; i<MAXVAL; i++){
    if(max<f[i]) max = f[i], lvls[0]=i, lvlsize=1;
    else if(max==f[i])lvls[lvlsize++] = i;
  }
  fprintf(fout, "%d\n", max);
  if(max>0){
    for(int i=0; i<lvlsize; i++){
      fprintf(fout, "%d ", lvls[i]);
    }
    fprintf(fout, "\n");
  }
  fclose(fout);
  return 0;
}
