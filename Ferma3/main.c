#include <stdio.h>
#include <string.h>

#define MAXN 400
#define BORDER -1
#define DIR 4

typedef struct{
  short int lin;
  short int col;
}_pos;

typedef struct{
  _pos pos;
  int val;
  char c;
}_type;

int n, m;
char mat[MAXN+3][MAXN+3];
int fill[MAXN+3][MAXN+3];
int v[MAXN*MAXN+7];

char dirLin[DIR] = {-1, 0, 1, 0};
char dirCol[DIR] = {0, 1, 0, -1};

int fillval = 1;

int flood(int l, int c, int control){
  if(fill[l][c] || mat[l][c] != control)
    return 0 ;
  fill[l][c] = fillval;
  int count = 0;
  for(int i=0; i<DIR; i++){
    count += flood(l+dirLin[i], c+dirCol[i], control);
  }
  return count+1;
}

_type surround(int i, int j){
  _type arr[DIR];
  int save[DIR];
  memset(arr, 0, sizeof(arr));
  memset(save, -1, sizeof(save));
  for(int d=0; d<DIR; d++){
    int l = i+dirLin[d];
    int c = j+dirCol[d];
    
    int i;
    for(i=d-1; i>=0; i--){
      if(save[i]==fill[l][c]) break;
    }
    if(i>=0) continue;
    
    arr[d].pos = (_pos){l, c};
    arr[d].val = v[fill[l][c]];
    arr[d].c =  mat[l][c];
    save[d] = fill[l][c];
  }

  _type max = (_type) {(_pos){0, 0}, 0, 0};
  for(int i=0; i<DIR; i++){
    for(int j=i+1; j<DIR; j++){
      if(arr[i].c==arr[j].c)arr[i].val+=arr[j].val;
      if(arr[i].val>max.val){max = arr[i];}
    }
  }

  if(mat[i][j]!=max.c) max.val++;
  return max;
}

int main(){
  int p;
  FILE *fin, *fout;
  fin=fopen("ferma3.in", "r");
  fscanf(fin, "%d\n%d %d\n", &p, &n, &m);
  for(int i=1; i<=n; i++){
    for(int j=1; j<=m; j++){
      mat[i][j] = fgetc(fin);
    }
    fgetc(fin); // endl
  }
  fclose(fin);

  for(int i=0; i<=n+1; i++)
    mat[i][0] = mat[i][m+1] = BORDER;
  for(int i=0; i<=m+1; i++)
    mat[0][i] = mat[n+1][i] = BORDER;

  int maxone = 0;
  for(int i=1; i<=n; i++){
    for(int j=1; j<=m; j++){
      if(!fill[i][j]){
        v[fillval] = flood(i, j, mat[i][j]);
        if(v[fillval]>maxone)
          maxone = v[fillval];
        fillval++;
      }
    }
  }

  _type max = (_type) {(_pos){0, 0}, 0, 0};
  for(int i=1; i<=n; i++){
    for(int j=1; j<=m; j++){
      _type val = surround(i, j);
      val.pos = (_pos){i, j};
      if(val.val>max.val){
        max = val;
      }
    }
  }

  fout=fopen("ferma3.out", "w");
  if(p==1)
    fprintf(fout, "%d\n", maxone);
  else
    fprintf(fout, "%d %d\n%c\n", max.pos.lin, max.pos.col, max.c);
  fclose(fout);
  return 0;
}
