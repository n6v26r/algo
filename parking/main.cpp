#include <iostream>
#include <list>
#include <string.h>
#define MAXN 1003

typedef struct{
  int lin;
  int col;
  int type;
}car;

int n, p, m, k, q;

bool holesCUp[MAXN];
bool holesCDown[MAXN];
bool holesLUp[MAXN];
bool holesLDown[MAXN];

std::list<car> masiniL[MAXN];
std::list<car> masiniC[MAXN];

bool rmv[MAXN][MAXN];
char mat[MAXN][MAXN];

int exit(){
  int total = 0;
  for(int i=1; i<n; i++){
      printf("%d: %d {%d %d} {%d %d} (%d %d)=>",i, masiniL[i].size(),
           masiniL[i].front().lin, masiniL[i].front().col,masiniL[i].back().lin, masiniL[i].back().col,
           holesLDown[i], holesLUp[i]); fflush(stdout);

    if(masiniL[i].size()>0 && holesLDown[i] && masiniL[i].front().type==0) masiniL[i].front().type = -1, rmv[masiniL[i].front().lin][masiniL[i].front().col] = true, total++;
    if(masiniL[i].size()>0 && holesLUp[i] && masiniL[i].back().type==0) masiniL[i].back().type = -1, rmv[masiniL[i].back().lin][masiniL[i].back().col] = true, total++;
    printf("%d\n", total);
  }

  for(int i=1; i<m; i++){
      printf("%d: %d {%d %d} {%d %d} (%d %d)=>",i, masiniC[i].size(),
           masiniC[i].front().lin, masiniC[i].front().col,masiniC[i].back().lin, masiniC[i].back().col,
           holesCDown[i], holesCUp[i]); fflush(stdout);

    if(masiniC[i].size()>0 && holesCDown[i] && masiniC[i].front().type==1) masiniC[i].front().type = -1, rmv[masiniC[i].front().lin][masiniC[i].front().col] = true, total++;
    if(masiniC[i].size()>0 && holesCUp[i] && masiniC[i].back().type==1) masiniC[i].back().type = -1, rmv[masiniC[i].back().lin][masiniC[i].back().col] = true, total++;
    printf("%d\n", total);
  }


  for(int i=0; i<m; i++){
    for(auto j = masiniC[i].begin(); j!=masiniC[i].end();){
      if(rmv[(*j).lin][(*j).col] || (*j).type == -1) j = masiniC[i].erase(j);
      else j++;
    }
  }

  for(int i=0; i<n; i++){
      for(auto j = masiniL[i].begin(); j!=masiniL[i].end();){
      if(rmv[(*j).lin][(*j).col] || (*j).type == -1) j = masiniL[i].erase(j), rmv[(*j).lin][(*j).col] = false;
      else j++;
    }
  }
  return total;
}

int main(){
  memset(mat, -1, sizeof(mat));
  FILE *fin, *fout;
  fin = fopen("parking.in", "r");
  fscanf(fin, "%d%d%d%d%d", &p, &n, &m, &k, &q); n++, m++;
  for(int i=0; i<k; i++){
    int l, c; fscanf(fin, "%d%d", &l, &c);
    if(c==0) holesLDown[l] = 1;
    else if(c==m) holesLUp[l] = 1;
    if(l==0) holesCDown[c] = 1;
    else if(l==n) holesCUp[c] = 1;
  }
  for(int i=0; i<q; i++){
    int lin, col, sens; fscanf(fin, "%d%d%d", &lin, &col, &sens);
    mat[lin][col] = sens;
  }
  fclose(fin);
  //if(p==2) return 0;

  for(int lin=1; lin<n; lin++){
    for(int col=1; col<m; col++){
      if(mat[lin][col] == -1) continue;
      masiniC[col].push_back((car){col, lin, mat[lin][col]});
      masiniL[lin].push_back((car){col, lin, mat[lin][col]});
    }
  }

  fout = fopen("parking.out", "w");
  if(p==1){
    fprintf(fout, "%d", exit());
  }
  else{
    int runde = 0;
    int total = 0;
    int cars;
    do{
      cars = exit();
      printf("%d ", cars);
      total+=cars;
      runde++;
    }while(cars>0);
    fprintf(fout, "%d %d\n", total, runde-1);
  }
  fclose(fout);
}
