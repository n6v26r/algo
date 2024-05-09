// ⠀⠀⠀⠀⣀⣀⣤⣤⣦⣶⢶⣶⣿⣿⣿⣿⣿⣿⣿⣷⣶⣶⡄⠀⠀⠀⠀⠀⠀⠀
// ⠀⠀⠀⠀⣿⣿⣿⠿⣿⣿⣾⣿⣿⣿⣿⣿⣿⠟⠛⠛⢿⣿⡇⠀⠀⠀⠀⠀⠀⠀
// ⠀⠀⠀⠀⣿⡟⠡⠂⠀⢹⣿⣿⣿⣿⣿⣿⡇⠘⠁⠀⠀⣿⡇⠀⢠⣄⠀⠀⠀⠀
// ⠀⠀⠀⠀⢸⣗⢴⣶⣷⣷⣿⣿⣿⣿⣿⣿⣷⣤⣤⣤⣴⣿⣗⣄⣼⣷⣶⡄⠀⠀
// ⠀⠀⠀⢀⣾⣿⡅⠐⣶⣦⣶⠀⢰⣶⣴⣦⣦⣶⠴⠀⢠⣿⣿⣿⣿⣼⣿⡇⠀⠀
// ⠀⠀⢀⣾⣿⣿⣷⣬⡛⠷⣿⣿⣿⣿⣿⣿⣿⠿⠿⣠⣿⣿⣿⣿⣿⠿⠛⠃⠀⠀
// ⠀⠀⢸⣿⣿⣿⣿⣿⣿⣿⣶⣦⣭⣭⣥⣭⣵⣶⣿⣿⣿⣿⣟⠉⠀⠀⠀⠀⠀⠀
// ⠀⠀⠀⠙⠇⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⡟⠀⠀⠀⠀⠀⠀⠀
// ⠀⠀⠀⠀⠀⣿⣿⣿⣿⣿⣛⠛⠛⠛⠛⠛⢛⣿⣿⣿⣿⣿⡇⠀⠀⠀⠀⠀⠀⠀
// ⠀⠀⠀⠀⠀⠿⣿⣿⣿⠿⠿⠀⠀⠀⠀⠀⠸⣿⣿⣿⣿⠿⠇⠀⠀⠀⠀⠀

// ONI 2022 baraj juniori
// __razv was here
#include <stdio.h>
#include <algorithm>
#include <vector>
#define MAXN 2222

typedef struct{
  int lin;
  int col;
}cell;

int n, k, ls, cs;
int cz, ct, cp;

int dirLin[] = {-1, 0, 1, 0};
int dirCol[] = {0, 1, 0, -1};

int mat[3][MAXN][MAXN];

int inBounds(int lin, int col){
  return lin>=0 && lin<n && col>=0 && col<n;
}

void mars(std::vector<cell> v, int mat[MAXN][MAXN]){
  if(inBounds(v[0].lin, v[0].col))mat[v[0].lin][v[0].col] ++;
  if(inBounds(v[1].lin, v[1].col))mat[v[1].lin][v[1].col] --;

  if(inBounds(v[2].lin, v[2].col))mat[v[2].lin][v[2].col] --;
  if(inBounds(v[3].lin, v[3].col))mat[v[3].lin][v[3].col] ++;
}

int main(){
  bool valid = 1;
  FILE *fin, *fout;
  fin = fopen("autostrada.in", "r");
  fout = fopen("autostrada.out", "w");
  fscanf(fin, "%d%d%d%d%d%d%d", &n, &k, &ls, &cs, &cz, &ct, &cp); ls--; cs--;
  for(int i=0; i<k; i++){
    int dir, dist;
    fscanf(fin, "%d%d", &dir, &dist);
    if(inBounds(ls+dirLin[dir]*dist, cs+dirCol[dir]*dist)){
      switch(dir){
        case 0:
          mars({ {ls-dist+1, cs}, {ls-dist+1, cs+1}, {ls, cs}, {ls, cs+1} }, mat[0]);
          break;
        case 1:
          mars( { {ls, cs+1}, {ls, cs+dist}, {ls+1, cs+1}, {ls+1, cs+dist} }, mat[1]);
          break;
        case 2:
          mars( { {ls+1, cs}, {ls+dist, cs}, {ls+1, cs+1}, {ls+dist, cs+1} }, mat[0]);
          break;
        case 3:
          mars({ {ls, cs-dist+1}, {ls, cs}, {ls+1, cs-dist+1}, {ls+1, cs} }, mat[1]);
          break;
        default:
          break;
      }
      mat[2][ls][cs] |= (1<<dir);
      ls+=dirLin[dir]*dist;
      cs+=dirCol[dir]*dist;
      mat[2][ls][cs] |= (1<<((dir+2)%4));
    }
    else{
      fprintf(fout, "TRASEU INVALID\n%d\n", i+1);
      valid = 0;
      break;
    }
  }
  if(!valid) return 0;
  fprintf(fout, "TRASEU VALID\n");
  for(int i=0; i<n; i++){
    for(int j=0; j<n; j++){
      mat[0][i][j] += (i>0?mat[0][i-1][j]:0)+(j>0?mat[0][i][j-1]:0)-(i>0 && j>0? mat[0][i-1][j-1]:0);
      mat[1][i][j] += (i>0?mat[1][i-1][j]:0)+(j>0?mat[1][i][j-1]:0)-(i>0 && j>0? mat[1][i-1][j-1]:0);
    }
  }

  int total = 0;
  int t = 0;
  int p = 0;
  for(int i=0; i<n; i++){
    for(int j=0; j<n; j++){
      bool v = (mat[0][i][j]>0 || (mat[2][i][j]&5)==5);
      bool h = (mat[1][i][j]>0 || (mat[2][i][j]&10)==10);
      
      bool halfV = (((mat[2][i][j]&1)==1) ^ ((mat[2][i][j]&4)==4));
      bool halfH = (((mat[2][i][j]&2)==2) ^ ((mat[2][i][j]&8)==8));

      if(mat[0][i][j] || mat[1][i][j] || mat[2][i][j]) total++;
      if(h && v) p++;
      else if((h && halfV) || (v && halfH)) t++;
    }
  }
  fprintf(fout, "%lld\n", (long long)(total-t-p)*cz + (long long)t*ct + (long long)p*cp);
  fclose(fin);
  fclose(fout);
}
