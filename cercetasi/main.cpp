#include <iostream>
#include <stdio.h>

using namespace std;

#define MAXN 10006

int n;
int v[MAXN];

int main(){
  FILE *fin, *fout;
  fin = fopen("cercetasi.in", "r");
  fscanf(fin, "%d", &n);
  for(int i=1; i<=n; i++){
    fscanf(fin, "%d", &v[i]);
  }
  fclose(fin);

  int m = 1;
  while(n%m==0){
    int a = n/m-m+1;
    if(a<0) break;
    m*=2;
  }

  m/=2;
  fout = fopen("cercetasi.out", "w");
  fprintf(fout, "%d\n", m);
  for(int i=(n/m-m+1); i<=(n/m-m+1 + 2*(m-1)); i+=2)
    fprintf(fout, "%d ", i);
  fprintf(fout, "\n");
  int total = 0;
  for(int a=(n/m-m+1); a<=(n/m-m+1 + 2*(m-1)); a+=2){
    if(v[a]==a) v[a] = -1;
    while(v[a]!=-1){
      int aux = a;
      a = v[a];
      v[aux] = -1;
      total++;
    }
  }
  fprintf(fout, "%d\n", total);
  fclose(fout);
}
