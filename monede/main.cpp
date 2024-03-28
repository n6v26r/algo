// ONI 2014 baraj juniori
// https://kilonova.ro/problems/1079
#include <stdio.h>
#include <iostream>
#include <algorithm>

#define MAXN 1000

int n, m;

int mat[MAXN][MAXN];

int main(){
  FILE * fin, *fout;
  fin = fopen("monede.in", "r");
  fscanf(fin, "%d%d", &n, &m);
  long long sum = 0;
  for(int i=0; i<n; i++){
    for(int j=0; j<m; j++){
      fscanf(fin, "%d", &mat[j][i]);
      sum += mat[j][i];
    }
  }
  fclose(fin);

  int med = sum/n;

  for(int i=0; i<m; i++)
    std::sort(mat[i], mat[i]+n);

  long long mv = 0;
  for(int i=0; i<n; i++){
    int s = 0;
    for(int j=0; j<m; j++) s += mat[j][i];
    if(s>med) mv += s-med;
  }

  fout = fopen("monede.out", "w");
  fprintf(fout, "%lld\n", mv);
  fclose(fout);
  return 0;
}
