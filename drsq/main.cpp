#include <iostream>
#include <fstream>
#include <math.h>
using namespace std;

#define MAXN 200000

int v[MAXN];
long long blocks[1000];
int blockSize;
int blockCount;

void update(int i, int val){
  int ib = i/blockSize;
  blocks[ib] += val-v[i];
  v[i] = val;
}

long long get(int a, int b){
  long long sum = 0;
  printf("%d %d\n", a, ceil((float)(a)/blockSize)*blockSize);
  for(int i=a; i<ceil((float)(a)/blockSize)*blockSize; i++)
    sum += v[i];
  for(int i=ceil((float)(a)/blockSize); i<b/blockSize; i++)
    sum += blocks[i];
  for(int i=(b/blockSize)*blockSize; i<=b; i++)
    sum += v[i];
  return sum;
}

int main(){
  ifstream cin("file.in");
  ofstream cout("file.out");
  int n, k;
  cin>>n>>k;

  for(int i=0; i<n; i++){
    cin>>v[i];
  }
  blockCount = ceil(sqrt(n));
  blockSize = n/blockCount;

  for(int i=0; i<n; i++){
    blocks[i/blockSize]+=v[i];
  }

  for(int i=0; i<k; i++){
    int p, a, b;
    cin>>p>>a>>b;
    if(p==1){
      update(a-1, b);
    }
    else cout<<get(a-1, b-1)<<endl;
  }

  return 0;
}
