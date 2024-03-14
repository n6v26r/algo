// OJI 2014 8th grade
// https://www.nerdarena.ro/problema/arrows
#include <stdio.h>
#include <stdbool.h>

#define MAXN 503
#define DIR 4
#define BORDER -1

typedef struct{
  char b;
  int steps;
  bool isOptim;
}node;

node mem[MAXN+1][MAXN+1];

int p, n, m;
int mat[MAXN][MAXN];
int dirLin[DIR] = {0, -1, 0, 1};
int dirCol[DIR] = {1, 0, -1, 0};

void border(){
  for(int i=0; i<=n+1; i++)
    mat[i][m+1] = mat[i][0] = BORDER;
  for(int j=0; j<=m+1; j++)
    mat[n+1][j] = mat[0][j] = BORDER;
}

int main(){
  int rl, rc;
  FILE *fin, *fout;
  fin = fopen("arrows.in", "r");
  fscanf(fin, "%d%d%d", &p, &n, &m);
  for(int i=1; i<=n; i++){
    for(int j=1; j<=m; j++){
      fscanf(fin, "%d", &mat[i][j]);
      mat[i][j]--;
    }
  }
  fscanf(fin, "%d%d", &rl, &rc);
  fclose(fin);

  border();

  for(int i=1; i<=n; i++){
    for(int j=1; j<=m; j++){
      int lin = i;
      int col = j;
      int steps = 0;

      while(mem[lin][col].b == 0){
        if(mat[lin][col]==BORDER) break;
        steps++;
        int nextLin = lin + dirLin[mat[lin][col]];
        int nextCol = col + dirCol[mat[lin][col]];
        mem[lin][col] = (node){1, 0};

        lin = nextLin;
        col = nextCol;
      }
      bool isOptim = false;
      if(mem[lin][col].b==1) isOptim=true;
      else if(mem[lin][col].isOptim) isOptim=true;
      steps+=mem[lin][col].steps;

      int l=i;
      int c=j;
      int partialSteps = 0;
      while(l!=lin || c!=col){
        int nextLin = l + dirLin[mat[l][c]];
        int nextCol = c + dirCol[mat[l][c]];

        partialSteps++;

        l = nextLin;
        c = nextCol;
      }

      while(mem[lin][col].b == 1){
        int nextLin = lin + dirLin[mat[lin][col]];
        int nextCol = col + dirCol[mat[lin][col]];
        mem[lin][col] = (node) {2, (steps-partialSteps), isOptim};

        lin = nextLin;
        col = nextCol;
      }

      l=i;
      c=j;

      while(l!=lin || c!=col){
        int nextLin = l + dirLin[mat[l][c]];
        int nextCol = c + dirCol[mat[l][c]];
        mem[l][c] = (node) {2, steps, isOptim};
        steps--;

        l = nextLin;
        c = nextCol;
      }
    }
  }

  int max=0, optimal = 0;
  for(int i=1; i<=n; i++){
    for(int j=1; j<=m; j++){
      int score = mem[i][j].steps;
      if(mem[i][j].isOptim) score*=1000, optimal++;
      if(score>max){
        max = score;
      }
    }
  }

  fout = fopen("arrows.out", "w");
  if(p==1)
    fprintf(fout, "%d\n", mem[rl][rc].steps*(mem[rl][rc].isOptim?1000:1));
  else if(p==3)
    fprintf(fout, "%d\n", max);
  else
    fprintf(fout, "%d\n", optimal);
  fclose(fout);
  return 0;
}
