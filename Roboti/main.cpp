#include <iostream>
#include <cstring>
#define MAXN 400

using namespace std;

int q;

int mat[MAXN][MAXN];
char been[MAXN][MAXN];

int dirLin[4] = {-1, 0, 1, 0};
int dirCol[4] = {0, 1, 0, -1};

int main(){
  int n, m, k;
  freopen("file.in", "r", stdin);
  freopen("file.out", "w", stdout);
  scanf("%d%d%d", &m, &n, &k);
  for(int i=0; i<k; i++){int l; int c; char dir; scanf("%d %d %c", &l, &c, &dir);
    mat[l-1][c-1] = (dir=='L'?-1:1);
  }
  scanf("%d", &q);
  for(int z=0; z<q; z++){
    int i, j, l, c;
    scanf("%d %d %d %d", &i, &j, &l, &c); i--; l--; j--; c--;
    if(k==0){
      if(i==l || j==c) printf("0\n");
      else printf("-1\n");
    }
    else{
      int turns;
      int mint = 2000000000;
      for(int d = 0; d<4; d++){
        int dir = d;
        memset(been, 0, sizeof(been));
        been[i][j] = 1;
        int x = i+dirLin[dir];
        int y = j+dirCol[dir];
        if(x<0) x = n-1;
        if(y<0) y = m-1;
        if(x>=n) x = 0;
        if(y>=n) y = 0;
        turns = 0;
        while(!((x==l && y==c) || been[x][y])){
          been[x][y] = 1;
          if(mat[x][y]!=0) dir = (dir+4+mat[x][y])%4, turns++;
          //printf(":%d %d %d \n", x, y, d);
          x+=dirLin[dir];
          y+=dirCol[dir];
          if(x<0) x = n-1;
          if(y<0) y = m-1;
          if(x>=n) x = 0;
          if(y>=n) y = 0;
        }
        if(!been[x][y] && turns<mint) mint = turns;
      }
      if(mint==2000000000) printf("-1 \n");
      else printf("%d\n", mint);
    }
  }
  return 0;
}
