#include <iostream>
#include <math.h>
using namespace std;

#define MAXN 100000

int nr[MAXN+1];
int v[MAXN+1];
int blocks[MAXN+1];
int blockSize;
int blockCount;

void update(int i, int val){
  blocks[i/blockSize] += val;
  v[i] += val;
}

int get(int j){
  int sum = 0;
  for(int i=0; i<j/blockSize; i++)
    sum+=blocks[i];
  for(int i=(j/blockSize)*blockSize; i<=j; i++)
    sum+=v[i];
  return sum;
}

int main(){
  int n;
  FILE *fin, *fout;
  fin = stdin;
  fout = stdout;
  fscanf(fin, "%d", &n);
  blockCount = ceil(sqrt(n));
  blockSize = n/blockCount;
  for(int i=0; i<n; i++){
   fscanf(fin, "%d", &nr[i]);
   fprintf(fout, "%d ", get(nr[i]));
   update(nr[i], 1);
  }
  fprintf(fout, "\n");

  fclose(fin);
  fclose(fout);
  return 0;
}
