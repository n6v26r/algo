include <iostream>
#include <fstream>
#include <unistd.h>
#define MAXN 200000

using namespace std;

long long aib[MAXN+2], n;
int v[MAXN+2];

void update(int i, long long val){
  while(i<=n){
    aib[i]+=val;
    i+=(i&-i);
  }
}

long long get(int i){
  long long sum = 0;
  while(i>0){
    sum+=aib[i];
    i-=(i&-i);
  }
  return sum;
}

int main(){
  //ifstream cin("file.in");
  //ofstream cout("file.out");
  int k;
  cin>>n>>k;
  for(int i=0; i<n; i++){
    int val;
    cin>>val;
    update(i+1, val);
    v[i+1] = val;
  }
  for(int i=0; i<k; i++){
    int p, a, b;
    cin>>p>>a>>b;
    if(p==1){
      update(a, b-v[a]);
      v[a] = b;
    }
    else cout<<get(b)-get(a-1)<<endl;
  }
  return 0;
