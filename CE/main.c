#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define MAXN 10000
#define BORDER -1
#define DIRHOLE 4
#define DIRREGIONS 8

int t;
int mat[MAXN+3][MAXN+3];
int n, m;
int dirLinH[DIRHOLE] = {-1, 0, 1, 0};
int dirColH[DIRHOLE] = {0, 1, 0, -1};
int dirLinR[DIRREGIONS] = {-1, -1, 0, 1, 1, 1, 0, -1};
int dirColR[DIRREGIONS] = {0, 1, 1, 1, 0, -1, -1, -1};

bool valid;

int l;
int c;
int dir;
int *dirLin;
int *dirCol;
int control;

void fill(){
  if(mat[l][c]!=control){ 
    if(mat[l][c]==BORDER && control==0)
      valid = false; 
    return;
  }
  mat[l][c] = BORDER-1;
  for(int i=0; i<dir; i++){
    l+=dirLin[i];
    c+=dirCol[i];
    fill();
    l-=dirLin[i];
    c-=dirCol[i];
  }
}

int main(){
  FILE *fin, *fout;
  fin=fopen("ce.in", "r");
  fout=fopen("ce.out", "w");
  fscanf(fin, "%d\n", &t);
  while(t>0){
    fscanf(fin, "%d\n%d\n", &n, &m);
    for(int i=1; i<=n; i++){
      for(int j=1; j<=m; j++){
        char c = fgetc(fin);
        if(c=='X') mat[i][j] = 1;
        else mat[i][j] = 0;
      }fgetc(fin);
    }
    for(int i=0; i<=n+1; i++)
      mat[i][0] = mat[i][m+1] = BORDER;
    for(int j=0; j<=m+1; j++)
      mat[0][j] = mat[n+1][j] = BORDER;

    int regions = 0;
    int holes = 0;
    for(int i=1; i<=n; i++){
      for(int j=1; j<=m; j++){ 
        if(mat[i][j]>0){
          l = i;
          c = j;
          dir = DIRREGIONS;
          dirLin = dirLinR;
          dirCol = dirColR;
          control = mat[i][j];
          fill();
          regions++;
        }
        else if(!mat[i][j]){
          valid = true;
          l = i;
          c = j;
          dir = DIRHOLE;
          dirLin = dirLinH;
          dirCol = dirColH;
          control = mat[i][j];
          fill();
          holes+=valid;
        }
      }
    }
    fprintf(fout, "%d\n", regions-holes);
    t--;
  }

  fclose(fout); 
  fclose(fin);
  return EXIT_SUCCESS;
}
