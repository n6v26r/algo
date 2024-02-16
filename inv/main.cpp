#include <iostream>
#include <bits/stdc++.h>
#define MAXN 100000
#define MOD 9917

using namespace std;

int aib[MAXN+2], n;
int v[MAXN+2];
int org[MAXN+2];

void update(int i, int val){
  while(i<n){
    aib[i]+=val;
    i+=(i&-i);
  }
}

int get(int i){
  int sum = 0;
  while(i>0){
    sum+=aib[i];
    i-=(i&-i);
  }
  return sum;
}

int main(){
  ifstream fin("inv.in");
  ofstream fout("inv.out");
  fin>>n;
  for(int i=1; i<=n; i++){
    fin>>v[i];
    org[i] = v[i];
  }
  sort(v+1, v+n+1);
  int total=0;
  for(int i=n; i>=0; i--){
    int s=1, d = n+1;
    while(d-s>1){
      int m = (s+d)/2;
      if(v[m]>org[i])
        d = m;
      else s = m;
    }
    total=(total+(get(s-1))%MOD)%MOD;
    update(s, 1);
  }
  fout<<total<<'\n';
  return 0;
}
