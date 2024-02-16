#include <stdio.h>
#include <ctype.h>
 
#define BORDER -128
#define MAXSIZE 100
#define DIR 4
#define QUEUESIZE 256
 
 
typedef struct Node{
  char l;
  char c;
}node;
 
node q[QUEUESIZE]; int p, u;
short int map[MAXSIZE+2][MAXSIZE+2]; int n, m;
char dirL[DIR] = {-1, 0, 1, 0};
char dirC[DIR] = {0, 1, 0, -1};
 
int insule[3];
 
void BFS(int ls, int cs, int fill, int dist){
  p=u=0;
  map[ls][cs] = fill;
  q[p].l = ls;
  q[p].c = cs;
  u++;
 
  int l;
  int c;
  do{
    l = q[p].l;
    c = q[p].c;
    p=(p+1)%QUEUESIZE;
 
    for(int i=0; i<DIR; i++){
      int lnext = l+dirL[i], cnext = c+dirC[i];
      if(!dist && map[lnext][cnext]!=-map[l][c]) continue;
      else if(dist && map[lnext][cnext] && map[lnext][cnext]<=map[l][c]+dist) continue;
      q[u].l = lnext;
      q[u].c = cnext;
      u=(u+1)%QUEUESIZE;
 
      map[lnext][cnext]=map[l][c]+dist;
    }
  }while(p!=u);
}
 
int main()
{
  FILE *fin, *fout;
  fin=fopen("insule.in", "r");
  fscanf(fin, "%d%d\n", &n, &m);
  for(int i=1; i<=n; i++){
    for(int j=1; j<=m; j++){
      map[i][j]=fgetc(fin);
      map[i][j]-='0';
    } fgetc(fin);
  }
  fclose(fin);
 
  for(int i=0; i<=n+1; i++){
    map[i][0]=map[i][m+1]=BORDER;
  }
  for(int i=0; i<=m+1; i++){
    map[0][i]=map[n+1][i]=BORDER;
  }
 
  for(int i=1; i<=n; i++){
    for(int j=1; j<=m; j++){
      if(map[i][j]>0){
        insule[map[i][j]-1]++;
        BFS(i, j, -map[i][j], 0);
      }
    }
  }
	
  for(int i=1; i<=n; i++){
    for(int j=1; j<=m; j++){
      if(map[i][j]==-1){
        BFS(i, j, 1, 1);
      }
    }
  }
  int min = __INT32_MAX__;
  for(int i=1; i<=n; i++){
    for(int j=1; j<=m; j++){
      if(map[i][j]==-2){
        for(int d=0; d<DIR; d++){
          if(map[i+dirL[d]][j+dirC[d]]>1 && map[i+dirL[d]][j+dirC[d]]<min)
            min = map[i+dirL[d]][j+dirC[d]];
        }
      }
    }
  }
 
  fout=fopen("insule.out", "w");
  fprintf(fout, "%d %d %d %d\n", insule[0], insule[1], insule[2], min-1);
  fclose(fout);
  return 0;
}
