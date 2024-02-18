#include <stdio.h>

#define MAXSIZE 1000
#define QUEUESIZE 1048576
#define DIR 4

typedef struct{
  short lin;
  short col;
}pos;

char mat[MAXSIZE+2][MAXSIZE+2];
int n, m;

int _bfs[MAXSIZE+2][MAXSIZE+2];
pos q[QUEUESIZE+1]; int p, u;
short dirLin[DIR] = {-1, 0, 1, 0};
short dirCol[DIR] = {0, 1, 0, -1};

pos newPos(short lin, short col){
  pos p = {lin, col};
  return p;
}

void bfs(){
  while(p!=u){
    pos node = q[p]; p = (p+1)%QUEUESIZE;
    int dist = _bfs[node.lin][node.col]; 

    for(char i=0; i<DIR; i++){
      pos next = {node.lin+dirLin[i], node.col+dirCol[i]};
      if(_bfs[next.lin][next.col]==-1 || (_bfs[next.lin][next.col]>0 && _bfs[next.lin][next.col]<=dist+1)){continue;}
      _bfs[next.lin][next.col] = dist+1;
      q[u] = next; u = (u+1)%QUEUESIZE;
    }
  }
}

int main(){
  FILE *fin, *fout;
  fin=fopen("dwarfland.in", "r");
  fscanf(fin, "%d %d\n", &n, &m);
  for(short i=1; i<=n; i++){
    for(short j=1; j<=m; j++){
      mat[i][j] = fgetc(fin); 
    }
    fgetc(fin);
  }
  fclose(fin);

  for(short i=0; i<=n+1; i++){
    mat[i][0]=mat[i][m+1]='Z';
  }
  for(short j=0; j<=m+1; j++){
    mat[0][j]=mat[n+1][j]='Z';
  }

  for(short i=0; i<=n+1; i++){
    for(short j=0; j<=m+1;j++){
      switch (mat[i][j]){
        case 'T':
          q[u] = newPos(i, j); u = (u+1)%QUEUESIZE;
          _bfs[i][j] = 1;
          break;
        case 'Z':
          _bfs[i][j] = -1;
          break;
        default:
          break;
      } 
    }
  }
  bfs();

  for(short i=0; i<=n+1; i++){
    for(short j=0; j<=m+1;j++){
      switch (mat[i][j]){
        case 'A':
          q[u] = newPos(i, j); u = (u+1)%QUEUESIZE;
          _bfs[i][j]--;
          break;
        case 'Z':
          _bfs[i][j] = -1;
          break;
        default:
          _bfs[i][j] = 0;
          break;
      } 
    }
  }
  
  bfs();

  int max = 0;
  for(short i=1; i<=n; i++){
    for(short j=1; j<=m; j++){
      if(mat[i][j]!='D') continue;
      if(_bfs[i][j]>max) max = _bfs[i][j];
    }
  }

  fout=fopen("dwarfland.out", "w");
  fprintf(fout, "%d\n", max);
  fclose(fout);
  return 0;
}
