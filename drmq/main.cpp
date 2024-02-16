#include <iostream>
#include <math.h>
using namespace std;

#define MAXN 200000

int v[MAXN+1];
int blocks[MAXN+1];
int blockSize;
int blockCount;

void update(int i, int val){
  v[i] = val;
  blocks[i/blockSize] = __INT_MAX__;
  for(int j=(i/blockSize)*blockSize; j<(i/blockSize+1)*blockSize; j++)
    if(v[j]<blocks[i/blockSize])blocks[i/blockSize]=v[j];
}

int get(int a, int b){
  int m = __INT_MAX__;
  int i;
  for(i = a; i<=b && i<=(a/blockSize+1)*blockSize; i++)
    if(v[i]<m) m = v[i];
  for(; i<b/blockSize; i+=blockSize)
    if(blocks[i/blockSize]<m) m = blocks[i/blockSize];
  for(; i<=b; i++)
    if(v[i]<m) m = v[i];
  return m;
}

int main(){
  int n, m;
  FILE *fin, *fout;
  fin = fopen("file.in", "r");
  fout = fopen("file.out", "w");
  //fin = stdin;
  //fout = stdout;
  fscanf(fin, "%d%d", &n, &m);
  blockCount = ceil(sqrt(n));
  blockSize = n/blockCount;
  for(int i=0; i<n; i++){
   fscanf(fin, "%d", &v[i]);
   update(i, v[i]);
  }

  for(int i=0; i<m; i++){
    int p, a, b;
    fscanf(fin, "%d%d%d", &p, &a, &b);
    if(p==1)update(a-1, b);
    else fprintf(fout, "%d\n", get(a-1, b-1));
  }

  fclose(fin);
  return 0;
}
