#include <iostream>
#include <stdio.h>
#include <bits/stdc++.h>
using namespace std;

#define MAXN 100000

long long v[MAXN+5];
long long aib[MAXN+2], n, m;

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
  FILE *fin, *fout;
  fin = fopen("aib.in", "r");
  fout = fopen("aib.out", "w");
  fscanf(fin, "%lld %lld\n", &n, &m);
  for(int i=1; i<=n; i++){
    fscanf(fin, "%lld ", &v[i]);
    update(i, v[i]);
  }
  for(int i=0; i<m; i++){
    long long type, a, b;
    fscanf(fin, "%lld %lld", &type, &a);
    if(type!=2) fscanf(fin, "%lld", &b);
    switch(type){
      case 0:
        update(a, b);
      break;
      case 1:
        fprintf(fout, "%lld\n", get(b)-get(a-1));
        break;
      case 2:
        long long s=1, d=n+1;
        while(d-s>1){
          int m = (s+d)/2;
          if(get(m)>a)
            d = m;
          else s = m;
        }
        if(get(s)!=a)
          fprintf(fout, "-1\n");
        else
          fprintf(fout, "%lld\n", s);
    }
  }
  return 0;
}
