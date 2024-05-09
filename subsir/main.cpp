#include <iostream>
#include <stdio.h>
#include <string.h>
using namespace std;

#define MAXN 10001

typedef struct{
  int first;
  int second;
}intPair;

int v[MAXN];

int pos[MAXN][10]; int posSize[10];
int cnt[MAXN][10];

int frecv[10000002];
int lastPos[1000002]; // save a bit of memory

int n, p, q;

int solve1(int val, int j){
  int cpy = val;
  int p10 = 1; while(p10*10<=val) p10*=10;
  int last = -1;
  while(p10>0){
    int cif = val/p10;
    int idx = (last>=0?cnt[last][cif]:0);
    if(idx>=posSize[cif] || pos[idx][cif]>j){if(cpy<100001)lastPos[cpy] = -1; return 0;}
    last = pos[idx][cif];

    val%=p10;
    p10/=10;
  }
  if(cpy<100001)lastPos[cpy] = last;
  return 1;
}

int main(){
  FILE *fin, *fout;
  fin = fopen("subsir.in", "r");
  fscanf(fin, "%d%d", &p, &n);
  for(int i=0; i<n; i++){
    fscanf(fin, "%d", &v[i]);
    pos[posSize[v[i]]++][v[i]] = i;
    for(int j=0; j<10; j++) cnt[i][j] = (i>0?cnt[i-1][j]:0);
    cnt[i][v[i]] ++;
  }

  if(p==2){
    for(int i=0; i<10; i++){
      frecv[i] = solve1(i, n-1);
      frecv[i]+=(i>0?frecv[i-1]:0);
    }
    for(int i=10; i<=10000000; i++){
      if(lastPos[i/10]>0){
        int last = lastPos[i/10];
        int cif = i%10;
        int idx = (last>=0?cnt[last][cif]:0);
        if(idx>=posSize[cif]){ frecv[i] = 0; if(i<=100000)lastPos[i] = -1;}
        else{
          frecv[i] = 1;
          if(i<=1000000)lastPos[i] = pos[idx][cif];
        }
      }
      else if(lastPos[i/10]==-1){ frecv[i] = 0; if(i<=1000000)lastPos[i] = -1;}
      else
        frecv[i] = solve1(i, n-1);
      frecv[i]+=(i>0?frecv[i-1]:0);
    }
  }

  fscanf(fin, "%d", &q);
  fout = fopen("subsir.out", "w");
  for(int i=0; i<q; i++){
    int a, b; fscanf(fin, "%d%d", &a, &b);
    if(p==1) fprintf(fout, "%d\n", solve1(a, b-1));
    else fprintf(fout, "%d\n", frecv[b]-frecv[a-1]);
  }
  fclose(fin);

  fclose(fout);
}
