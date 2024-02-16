#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAXN 100
#define BORDER __INT_MAX__
#define DIR 4

int mat[MAXN+3][MAXN+3], n, m;
bool border[MAXN+3][MAXN+3];
char dirLin[DIR] = {-1, 0, 1, 0};
char dirCol[DIR] = {0, 1, 0, -1};

bool status;

void floodfill(int l, int c, int lvl){
  if(mat[l][c] == BORDER) return;
  
  if(mat[l][c]!=lvl){ 
    if(mat[l][c]<lvl) status = true;
    return;
  }

  if(border[l][c]) return;
  border[l][c] = true;
  for(int i=0; i<DIR; i++){
    floodfill(l+dirLin[i], c+dirCol[i], lvl);
  }
  return;
}

int main(){
  FILE *fin, *fout;
  fin = fopen("drenaj.in", "r");
  fscanf(fin, "%d %d\n", &n, &m);
  for(int i=1; i<=n; i++){
    for(int j=1; j<=m; j++){
      fscanf(fin, "%d", &mat[i][j]);
    }
  }
  fclose(fin);

  for(int i=0; i<=n+1; i++)
    mat[i][0]=mat[i][m+1]=BORDER, border[i][0]=border[i][m+1]=true;
  for(int i=0; i<=m+1; i++)
    mat[0][i]=mat[n+1][i]=BORDER, border[0][i]=border[n+1][i]=true;
  
  int total = 0;
  for(int i=1; i<=n; i++){
    for(int j=1; j<=m; j++){
      if(!border[i][j]){
        status = false;
        floodfill(i, j, mat[i][j]);
        total+= !status;
        // printf("[%d][%d] => %d\n", i, j, status); fflush(stdout);
        // for(int i=1; i<=n; i++){
        //   for(int j=1; j<=m; j++){
        //     if(border[i][j]) printf("# ");
        //     else
        //       printf("%d ", mat[i][j]);
        //   }printf("\n");
        // }
      }
    }
  }

  fout = fopen("drenaj.out", "w");
  fprintf(fout, "%d\n", total);
  fclose(fout);
  return 0;
}
