// This crappy code is provided to u
// by __razv

// https://kilonova.ro/problems/1521/

#pragma GCC optimize("Ofast,unroll-loops")

#include <iostream>
#include <math.h>
#include <vector>

#define MAXMN 400001
#define MOD 1000000007

using namespace std;

vector<vector<int>> mat;

int f[MAXMN];

int sens = 1;
int m, n, l, k;

int batog[700]; int sizeB;

inline void add(int val){
  f[val]++;
  if(f[val] == 1){
    int idx = val/sizeB;
    batog[idx]++;
  }
}

inline void del(int val){
  f[val]--;
  if(f[val] == 0){
    int idx = val/sizeB;
    batog[idx]--;
  }
}

inline void movedownR(int &i, int &j){
  sens = -sens;
  i++;
  j -= k-1;
  for(int y=j; y<m; y++){
    add(mat[i][y]);
    del(mat[i-l][y]);
  }
}

inline void movedownL(int &i, int &j){
  sens = -sens;
  i++;
  j += k-1;
  for(int y=0; y<=j; y++){
    add(mat[i][y]);
    del(mat[i-l][y]);
  }
}

inline int mex(){
  int idx, pos;
  for(idx=0; idx<=sizeB && batog[idx]==sizeB; idx++);
  for(pos=idx*sizeB; pos<(idx+1)*sizeB && f[pos]>0; pos++);
  return pos;
}

inline void readInt(int *n, FILE *fin){
  *n = 0;
  char c = fgetc(fin);
  while(!isdigit(c)) c = fgetc(fin);
  while(isdigit(c)){(*n)=(*n)*10+c-'0'; c = fgetc(fin);}
}

int main(){
  FILE *fin, *fout;
  fin = fopen("mexitate.in", "r");
  fscanf(fin, "%d%d%d%d", &n, &m, &l, &k);
  bool swapped = 0;
  if(n>m){
    swap(n, m);
    swap(l, k);
    swapped = 1;
  }
  mat.resize(n+1);
  for(int i=0; i<n; i++){
    mat[i].resize(m+1);
  }
  if(!swapped){
    for(int i=0; i<n; i++){
      for(int j=0; j<m; j++){
        readInt(&mat[i][j], fin);
      }
    }
  }
  else{
    for(int i=0; i<m; i++){
      for(int j=0; j<n; j++){
        readInt(&mat[j][i], fin);
      }
    }
  }
  fclose(fin);

  sizeB = sqrt(n*m);

  long long prod = 1;

  int j, i;
  for(i=0; i<l; i++){
    for(j=0; j<k; j++){
      add(mat[i][j]);
    }
  }
  j--; i--;
  add(0);
  prod *= mex();
  while(prod>MOD) prod-=MOD;
  while(i<n){
    if(sens==1){
      while(j<m-1){
        j++;
        for(int y=i-l+1; y<=i; y++){
          add(mat[y][j]);
          del(mat[y][j-k]);
        }
        prod *= mex();
        while(prod>MOD) prod-=MOD;
      }
      if(i==n-1) break;
      movedownR(i, j);
      prod *= mex();
      while(prod>MOD) prod-=MOD;
    }
    else{
      while(j>0){
        j--;
        for(int y=i-l+1; y<=i; y++){
          add(mat[y][j]);
          del(mat[y][j+k]);
        }
        prod *= mex();
        while(prod>MOD) prod-=MOD;
      }
      if(i==n-1) break;
      movedownL(i, j);
      prod *= mex();
      while(prod>MOD) prod-=MOD;
    }
  }

  fout = fopen("mexitate.out", "w");
  fprintf(fout, "%lld\n", prod);
  fclose(fout);
  return 0;
}
