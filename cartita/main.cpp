#include <iostream>

#define MAXN 100000
#define MAXU 300000
#define MAXQ 200000
#define MIN(a, b) ((a)>(b)?(b):(a))
using namespace std;

int n, u, q;

int v[MAXN];

int m[MAXN];
int mm[MAXN];

int main(){
  FILE *fin, *fout;
  fin = fopen("cartita.in", "r");
  fscanf(fin, "%d", &n);
  for(int i=0; i<n; i++){
    fscanf(fin, "%d", &v[i]);
  }
  fscanf(fin, "%d", &u);
  for(int i=0; i<u; i++){
    int p, x, k;
    fscanf(fin, "%d%d%d", &p, &x, &k);

  }
  fclose(fin);

  fout = fopen("cartita.out", "w");
  fclose(fout);
  return 0;
}
