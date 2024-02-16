#include <iostream>
#include <bits/stdc++.h>
using namespace std;

#define MAXN 100000

long long v[MAXN+7], n;
long long p[MAXN+7];
long long aib[MAXN+7];
long long save[MAXN+7];

long long get(long long i){
  long long sum = 0;
  while(i>0){
    sum+=aib[i];
    i-=(i&(-i));
  }
  return sum;
}

void update(long long i, long long val){
  while(i<=n+1){
    aib[i]+=val;
    i+=(i&-i);
  }
}

int main(){
  ifstream fin("haircut.in");
  ofstream fout("haircut.out");
  fin>>n;
  for(int i=1; i<=n; i++){
    fin>>v[i];
    v[i]++;
    p[v[i]]=i;
  }
  for(int i=1; i<=n; i++){
    save[v[i]] += get(n+1)-get(v[i]);
    update(v[i], 1);
  }


  long long sum=0;
  fout<<sum<<'\n';
  for(int i=1; i<n; i++){
    sum += save[i];
    fout<<sum<<'\n';
  }
  return 0;
}
