#include <stdio.h>
#include <stdbool.h>
#include <ctype.h>
 
#define BORDER 1
#define EMPTY 0
#define MAXSIZE 175
#define QUEUESIZE 1024
#define DIR 4
 
typedef struct Node{
  int l;
  int c;
}node;
 
short int parc[MAXSIZE+2][MAXSIZE+2];
node q[QUEUESIZE]; int p = 0, u = 0;
int n, m;
 
char dirL[DIR] = {-1, 0, 1, 0};
char dirC[DIR] = {0, 1, 0, -1};
 
void readInt(int *n, FILE *fin){
  char c = fgetc(fin);
  *n = 0;
  while(!isdigit(c)) c=fgetc(fin);
  while(isdigit(c)){
    *n = (*n)*10+c-'0';
    c=fgetc(fin);
  }
}
 
int BFS(int lstart, int cstart, int lgoal, int cgoal){
  parc[lstart][cstart] = 2;
  q[p].l = lstart;
  q[p].c = cstart;
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
      if(parc[lnext][cnext]!=EMPTY) continue;
 
      q[u].l = lnext;
      q[u].c = cnext;
      u=(u+1)%QUEUESIZE;
 
      parc[lnext][cnext] = parc[l][c]+1;
 
      if(lnext==lgoal && cnext==cgoal)
        return parc[lgoal][cgoal];
    }
 
  }while(p!=u);
  return -1;
}
 
int main()
{
  FILE *fin, *fout;
  fin=fopen("alee.in", "r");
  fscanf(fin, "%d%d", &n, &m);
  int l, c;
  int lin, col;
  for(int i=0; i<m; i++){
    readInt(&l, fin); readInt(&c, fin);
    parc[l][c] = 1;
  }
  fscanf(fin, "%d%d%d%d", &l, &c, &lin, &col);
  fclose(fin);
 
  for(int i=0; i<=n+1; i++){
    parc[i][0]=parc[0][i]=parc[i][n+1]=parc[n+1][i] = BORDER;
  }
 
  int dist = BFS(l, c, lin, col);
 
  fout=fopen("alee.out", "w");
  fprintf(fout, "%d\n", dist-1);
  fclose(fout);
  return 0;
}
