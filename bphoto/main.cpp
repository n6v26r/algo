#include <iostream>
#include <bits/stdc++.h>
using namespace std;

#define MAXN 100000

int n;
int v[MAXN+2];
int org[MAXN+2];
int aib[MAXN+2];
int val[MAXN+2];

void update(int i, int val){
  while(i<=n){
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

int unbalanced(int a, int b){
  if(a>b) return a>2*b;
  else return b>2*a;
}

int main(){
  ifstream fin("bphoto.in");
  ofstream fout("bphoto.out");
  fin>>n;
  for(int i=1; i<=n; i++){
    fin>>v[i];
    org[i] = v[i];
  }
  sort(v+1, v+n+1);
  for(int i=n; i>0; i--){
    int s=1, d = n+1;
    while(d-s>1){
      int m = (s+d)/2;
      if(v[m]>org[i])
        d = m;
      else s = m;
    }
    val[i]=(get(n)-get(s));
    update(s, 1);
  }
  memset(aib, 0, sizeof(aib));
  int total = 0;
  for(int i=1; i<=n; i++){
    int s=1, d = n+1;
    while(d-s>1){
      int m = (s+d)/2;
      if(v[m]>org[i])
        d = m;
      else s = m;
    }
    int x = (get(n)-get(s));
    if(unbalanced(val[i], x))
      total++;
    update(s, 1);
  }
  fout<<total;
  return 0;
}
