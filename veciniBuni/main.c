#include <stdio.h>
#include <string.h>

#define MAXN 1009
#define BORDER 9

int n, k, m;
int mat[3][MAXN];
int l = 0;
int max=0, maxcnt=0;

void lvl(){
  if(l==0)memset(mat[0], -1, sizeof(mat[0]));
  if(l==n-1)memset(mat[2], -1, sizeof(mat[2]));
  for(int i=0; i<3; i++) mat[i][0]=mat[i][m+1] = -1;
  for(int i=1; i<=m; i++){
    int vb = -1;
    for(int lin = 0; lin<=2; lin++)
      for(int col = -1; col<=1; col++){
        if(mat[lin][i+col]==mat[1][i]) vb++;
      }
    if(vb>max){max=vb;maxcnt=1;}
    else if(vb==max){maxcnt++;}
  }
  memcpy(mat[0], mat[1], sizeof(mat[1]));
  memcpy(mat[1], mat[2], sizeof(mat[1]));
  memset(mat[2], 0, sizeof(mat[0]));
  l++;
}

int main(){
  FILE *fin, *fout;
  fin = fopen("vecini.in", "r");
  fscanf(fin, "%d%d%d", &n, &m, &k);
  int lin=-1, col=-1;
  int i = 0;
  while(i<k && l<n+1){
    fscanf(fin, "%d%d", &lin, &col);
    while(lin>l+2){
      lvl();
    } 
    mat[lin-l][col] = 1;
    i++;
  }
  fclose(fin);

  while(l<n){
    lvl();
  }

  fout = fopen("vecini.out", "w");
  fprintf(fout, "%d %d\n", max, maxcnt);
  fclose(fout);
  return 0;
}
