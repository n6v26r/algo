#include <iostream>
#include <bits/stdc++.h>
#include <string.h>
using namespace std;

#define MAXN 100001

int x, n, k;

int f[128];
string v;

int main(){
  ifstream fin("criptografie.in");
  ofstream fout("criptografie.out");
  fin >> x >> k >>n;
  fin >> v;
  int p = 0, u = -1;
  long long total = 0;
  int _max = 0;
  for(int i=0; i<n; i++){
    f[v[i]]++;
    while(f[v[i]]>k && p<=u){
      f[v[p]]--;
      p++;
    }
    u++;
    //printf("%d  %d\n", p, u);
    if(u-p+1>=_max){
      _max = u-p+1;
    }
    total += u-p+1;
  }

  if(x==2){
    string a;
    for(int i=0; i<n; i++){
      memset(f, 0, sizeof(f));
      int j;
      for(j = i; j<n; j++){
        if(f[v[j]]){
          break;
        }
        f[v[j]]++;
      }
      j--;
      if(j-i+1>a.size()){
        a=v.substr(i, j-i+1);
      }
      else if(j-i+1==a.size() && a>v.substr(i, j-i+1)){
        a=v.substr(i, j-i+1);
      }
    }
    fout << a;
  }
  if(x==1) fout << total << endl;
  return 0;
}
