#include <stdio.h>

#define DIR 4
#define MAXP 10001
#define MAXK 100001

typedef struct{
  int i;
  int j;
  int d;
}rata;

typedef struct{
  char type;
  int val;
}action;

typedef struct{
  int lin;
  int col;
}pos;

int n, p, k;
int dirLin[DIR] = {-1, 0, 1, 0};
int dirCol[DIR] = {0, 1, 0, -1};

int lastZ;
int dir;

rata rate[MAXP];
action v[MAXK];

pos finalPos[DIR];

char hasZ;

int main(){
  FILE *fin, *fout;
  fin = fopen("pelican.in", "r");
  fscanf(fin, "%d%d%d", &n, &p, &k);
  for(int i=0; i<p; i++){
    fscanf(fin, "%d%d%d", &rate[i].i, &rate[i].j, &rate[i].d); rate[i].d--;
  } fgetc(fin);
  for(int i=0; i<k; i++){
    v[i].type = fgetc(fin); if(v[i].type=='Z') hasZ = 1;
    fscanf(fin, "%d\n", &v[i].val);
  }
  fclose(fin);

  for(int d=0; d<DIR; d++){
    pos curr = {0, 0};
    int rotation = d;
    for(int i=0; i<k; i++){
      switch(v[i].type){
        case 'A':
          curr.lin+=dirLin[rotation]*v[i].val;
          curr.col+=dirCol[rotation]*v[i].val;

          curr.lin%=n; if(curr.lin<0) curr.lin+=n;
          curr.col%=n; if(curr.col<0) curr.col+=n;
          break;
        case 'R':
          rotation = (rotation+v[i].val)%4;
          break;
        case 'Z':
          curr.lin = v[i].val/n;
          curr.col = v[i].val%n;
          break;
        default:
          printf("CHEATING!!!\n");
          break;
      }
    }
    finalPos[d] = curr;
  }

  fout = fopen("pelican.out", "w");
  for(int i=0; i<p; i++){
    if(!hasZ)
      fprintf(fout, "%d %d\n", (rate[i].i+finalPos[rate[i].d].lin)%n, 
                               (rate[i].j+finalPos[rate[i].d].col)%n);
    else fprintf(fout, "%d %d\n", finalPos[rate[i].d].lin, finalPos[rate[i].d].col);
  }
  fclose(fout);
  return 0;
}
