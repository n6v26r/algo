#include <stdio.h>
#include <string.h>
 
#define MAXS 80
#define QUEUESIZE 8192
#define DIR 4
#define EMPTY -1
 
typedef struct{
  int l;
  int c;
}node;
 
char mat[MAXS+2][MAXS+2];
int fill[MAXS+2][MAXS+2];
node q[QUEUESIZE+1]; int p, u;
int dirL[DIR] = {-1, 0, 1, 0};
int dirC[DIR] = {0, 1, 0, -1};
 
int n, m;
 
int BFS(int lstart, int cstart, int lgoal, int cgoal){
  p=0;
  u=0;
  fill[lstart][cstart] = 0;
  q[u].l = lstart;
  q[u].c = cstart;
  u++;
  int l;
  int c;
 
  do{
    l = q[p].l;
    c = q[p].c;
    p=(p+1)%QUEUESIZE;
 
    for(int i=0; i<DIR; i++){
      int lnext = l+dirL[i];
      int cnext = c+dirC[i];
      if(!(lnext==lgoal && cnext==cgoal) && (mat[lnext][cnext]==EMPTY || mat[lnext][cnext]=='X')) continue;
      if(fill[lnext][cnext]>0 && fill[lnext][cnext]<fill[l][c]+1) continue;
 
      q[u].l = lnext;
      q[u].c = cnext;
      u=(u+1)%QUEUESIZE;
 
      fill[lnext][cnext] = fill[l][c]+1;
 
      if(lnext==lgoal && cnext==cgoal)
        return fill[lgoal][cgoal];
    }
  }while(p!=u);
  return -1;
}
 
int main()
{
    FILE *fin, *fout;
    fin=fopen("inginer.in", "r");
    fscanf(fin, "%d%d\n", &n, &m);
    for(int i=2; i<=n+1; i++){
      for(int j=2; j<=m+1; j++){
        mat[i][j]=fgetc(fin);
      }
      fgetc(fin);
    }
    for(int i=0; i<=n+3; i++){
      mat[i][0]=mat[i][m+3]=EMPTY;
    }
    for(int j=0; j<=m+3; j++){
      mat[0][j]=mat[n+3][j]=EMPTY;
    }
 
    fout=fopen("inginer.out", "w");
    while(1){
      int ls, cs, lg, cg;
      fscanf(fin, "%d%d%d%d", &ls, &cs, &lg, &cg);
      if(ls==cs && cs==lg && lg==cg && cg==0)
        break;
      BFS(ls+1, cs+1, lg+1, cg+1);
      fprintf(fout, "%d\n", fill[lg+1][cg+1]);
      memset(fill, 0, sizeof fill);
    }
    fclose(fout);
    fclose(fin);
    return 0;
}
