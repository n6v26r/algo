// ONI 2018 9th grade
// https://kilonova.ro/problems/1525
// Not a very good solution, but gets maximum score
#include <iostream>
#include <algorithm>
#include <string.h>

#define MAXN 1002
#define MAXQ 100001
#define MAX(a, b) ((a)>(b)?(a):(b))

typedef struct{
  int val;
  int idx;
} query;

int n, m, q;
int mat[MAXN][MAXN];

query Q[MAXQ];
query ans[MAXQ];

int hight[MAXN][MAXN];
int link[MAXN][MAXN];

int findLink[MAXN];

int frecv[MAXN];

bool compQuery(query a, query b){
  return a.val<b.val;
}

bool unsortQuery(query a, query b){
  return a.idx<b.idx;
}

int main(){
  FILE *fin, *fout;
  fin = fopen("rosiimici.in", "r");
  fscanf(fin, "%d%d%d", &n, &m, &q);
  for(int i=0; i<n; i++){
    for(int j=0; j<m; j++){
      fscanf(fin, "%d", &mat[j][i]);
    }
  }
  for(int i=0; i<q; i++) fscanf(fin, "%d", &Q[i].val), Q[i].idx = i;
  fclose(fin);

  std::sort(Q, Q+q, compQuery);
  for(int i=0; i<m; i++){
    int y = 0;
    int _y = 1;
    for(int j=0; j<n; j++){
      while(y<q && Q[y].val<mat[i][j]) y++;
      if(Q[y].val>=mat[i][j]){link[i][_y] = y+1; hight[i][_y++] = j+1;}
    }
  }

  for(int i=0; i<q; i++){
    memset(frecv, 0, sizeof(frecv));
    for(int col=0; col<m; col++){
      while(link[col][findLink[col]+1]==i+1) findLink[col]++;
      frecv[hight[col][findLink[col]]] ++;
    }
    int sz;
    int cnt = 0;
    int maxSize = 0;
    for(int i=n; i>0; i--){
      if(frecv[i]){
        sz = i;
        cnt += frecv[i];
        maxSize = MAX(maxSize, sz*cnt);
      }
    }
    ans[i] = (query){maxSize, Q[i].idx};
  }

  std::sort(ans, ans+q, unsortQuery);

  fout = fopen("rosiimici.out", "w");
  for(int i=0; i<q; i++){
    fprintf(fout, "%d\n", ans[i].val);
  }
  fclose(fout);
  return 0;
}
