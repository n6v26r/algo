// ONI 2011 baraj juniori
// __razv was here
#include <stdio.h>
#include <string.h>
 
#define MAXN 1001
#define MAX(a, b) ((a)>(b)?(a):(b))
 
int n, m;
 
int dirLin[4] = {-1, 0, 1, 0};
int dirCol[4] = {0, 1, 0, -1};
 
int mat[MAXN][MAXN];
int traseu[MAXN][MAXN];
char beenHere[MAXN][MAXN];
 
int drum;
 
bool inBounds(int l, int c){
  if(drum && l==0 && c==0) return 0;
  if(drum && l==n-1 && c==m-1) return 0;
  if(!drum && l==n-1 && c==0) return 0;
  if(!drum && l==0 && c==m-1) return 0;
  return l>=0 && c>=0 && l<n && c<m;
}
 
void mark(int l, int c, int a, int b){
  beenHere[l][c] ++;
  if(l==a && c==b) return;
  for(int i=0; i<4; i++){
    if(!inBounds(l+dirLin[i], c+dirCol[i])) continue;
    if(traseu[l+dirLin[i]][c+dirCol[i]] == traseu[l][c]-mat[l][c]){
      mark(l+dirLin[i], c+dirCol[i], a, b);
      break;
    }
  }
}
 
int main(){
  FILE *fin, *fout;
  fin = fopen("poteci.in", "r");
  fscanf(fin, "%d%d", &n, &m);
  for(int i=0; i<n; i++){
    for(int j=0; j<m; j++)
      fscanf(fin, "%d", &mat[i][j]);
  }
  fclose(fin);
 
  int total = 0;
 
  for(int i=n-1; i>=0; i--){
    for(int j=m-1; j>=0; j--){
      if(!inBounds(i, j)) continue;
      traseu[i][j] = MAX(traseu[i][j], mat[i][j]);
      if(inBounds(i+1, j)) traseu[i][j] = MAX(traseu[i][j], traseu[i+1][j]+mat[i][j]);
      if(inBounds(i, j+1)) traseu[i][j] = MAX(traseu[i][j], traseu[i][j+1]+mat[i][j]);
    }
  }
 
  total += traseu[0][0];
  mark(0, 0, n-1, m-1);
  memset(traseu, 0, sizeof(traseu));
  drum++;
  for(int i=0; i<n; i++){
    for(int j=m-1; j>=0; j--){
      if(!inBounds(i, j)) continue;
      traseu[i][j] = MAX(traseu[i][j], mat[i][j]);
      if(inBounds(i-1, j)) traseu[i][j] = MAX(traseu[i][j], traseu[i-1][j]+mat[i][j]);
      if(inBounds(i, j+1)) traseu[i][j] = MAX(traseu[i][j], traseu[i][j+1]+mat[i][j]);
    }
  }
 
  total += traseu[n-1][0];
  mark(n-1, 0, 0, m-1);
 
  fout = fopen("poteci.out", "w");
  fprintf(fout, "%d\n", total);
  for(int i=0; i<n; i++){
    int j = 0;
    for(j=0; j<m; j++)
      if(beenHere[i][j] == 2){
        fprintf(fout, "%d %d\n", i+1, j+1);
        break;
      }
    if(j<m) break;
  }
  fclose(fout);
  return 0;
}
