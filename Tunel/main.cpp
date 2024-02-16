#include <stdio.h>

#define MIN(a, b) ((a)<(b)?(a):(b))

#define MAXN 2002
#define MAXM 20002
#define DIR 4

int t, n, m, x;
char mat[MAXN][MAXM];
int dirLin[DIR] = {-2, 0, 2, 0};
int dirCol[DIR] = {0, 1, 0, -1};

int lock = -1;

int inBounds(int lin, int col){
  return (lin>=0 && col>=0 && lin<=2*(n-1) && col<m);
}

int cm(int lin, int col){
  if(!inBounds(lin, col)) return 0;
  if(!(lin%2)) mat[lin][col] = 1;
  return mat[lin][col];
}

int next(int lin, int col){
  if(!inBounds(lin, col)) return -1;
  if(lock!=0 && cm(lin-1, col)) return 0;
  if(lock!=2 && cm(lin+1, col)) return 2;
  if(cm(lin, col+1)) return 1;

  return -1;
}

int prev(int lin, int col){
  if(!inBounds(lin, col)) return -1;
  if(lock!=0 && cm(lin-1, col)) return 0;
  if(lock!=2 && cm(lin+1, col)) return 2;
  if(cm(lin, col-1)) return 3;

  return -1;
}

int traceback(int lin, int col){
  int dir = prev(lin, col);
  int len = 0;
  while(dir!=-1){
    if(!(lin%2)) mat[lin][col] = 1;
    len++;
    lin += dirLin[dir];
    col += dirCol[dir];
    if(dir!=3) lock = 2-dir, len++;
    else lock = -1;
    dir = prev(lin, col);
    if(lin%2==0 && col==0) break;
  }
  return len+1;
}

int main(){
  FILE *fin, *fout;
  fin = fopen("tunel.in", "r");
  fscanf(fin, "%d%d%d%d", &t, &n, &m, &x); x = 2*(x-1);
  for(int i=1; i<=n-1; i++){
    int val; fscanf(fin, "%d", &val);
    for(int j=0; j<val; j++){
      int pos; fscanf(fin, "%d", &pos);
      mat[2*(i-1)+1][pos-1] = 1;
    }
  }
  fclose(fin);

  int ans = 0;

  if(t==1){
    int lin = x;
    int col = 0;
    int dir = next(lin, col);
    while(dir!=-1){
      if(!(lin%2)) mat[lin][col] = 1;
      lin += dirLin[dir];
      col += dirCol[dir];
      if(dir!=1) lock = 2-dir;
      else lock = -1;
      dir = next(lin, col);
      if(lin==2*(n-1) && col==m-1) break;
    }
    ans = (lin)/2+1;
  }
  else{
    int b = 690000000;
    int a = traceback(2*(n-1), m-2);
    if(mat[2*(n-1)-1][m-1]){
      lock = 2;
      b = traceback(2*(n-1)-2, m-1);
    }

    ans = a+1;
    ans = MIN(a+1, b+2);
  }

  fout = fopen("tunel.out", "w");
  fprintf(fout, "%d\n", ans);
  fclose(fout);
  return 0;
}
