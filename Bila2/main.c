#include <stdbool.h>
#include <stdio.h>

#define MAXSIZE 1000
#define DIR 4

typedef struct{
  short lin;
  short col;
}coord;

short dirLin[DIR] = {-1, 0, 1, 0};
short dirCol[DIR] = {0, 1, 0, -1};

bool visited[MAXSIZE+1][MAXSIZE+1];
unsigned int drumuri[MAXSIZE+1][MAXSIZE+1];
short mat[MAXSIZE+1][MAXSIZE+1];
int n, m;

bool isCorner(coord pos){
  if((pos.lin==0 || pos.lin==n-1) && (pos.col == 0 || pos.col == m-1))
    return true;
  return false;
}

bool inBounds(coord pos){
  if(pos.lin>=0 && pos.lin<n && pos.col>=0 && pos.col<m)
    return true;
  else
    return false;
}

int dfs(coord pos){
  if(!inBounds(pos)) return -1;
  if(!visited[pos.lin][pos.col]){
    visited[pos.lin][pos.col] = true;
    for(int i=0; i<DIR; i++){
      coord new = {pos.lin+dirLin[i], pos.col+dirCol[i]};
      if(!inBounds(new)) continue;
      if(mat[new.lin][new.col] < mat[pos.lin][pos.col])
        drumuri[pos.lin][pos.col]+=dfs(new);
    }
    if(isCorner(pos)) {
      drumuri[pos.lin][pos.col]++;
    }
  }
  return drumuri[pos.lin][pos.col];
}

int main(){
  FILE *fin, *fout;
  fin = fopen("bila2.in", "r");
  fscanf(fin, "%d%d", &n, &m);
  for(int i=0; i<n; i++){
    for(int j=0; j<m; j++){
      fscanf(fin, "%hd", &mat[i][j]);
    }
  }
  coord start;
  fscanf(fin, "%hd %hd", &start.lin, &start.col);
  start.lin--;
  start.col--;
  fclose(fin); 

  fout = fopen("bila2.out", "w");
  fprintf(fout, "%u\n", dfs(start));
  fclose(fout);
}
