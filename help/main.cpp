#include <iostream>
#include <bits/stdc++.h>
using namespace std;

#define MAXN 100000
#define MOD 1000000007

ifstream fin("help.in");
ofstream fout("help.out");

typedef struct{
  int a;
  int b;
}interval;

int n;
interval v[MAXN+7];
int mars[2*MAXN+7];
int _pow[MAXN+7];

void calcPow(int b){
  int i =1;
  int p = 1;
  _pow[0]=1;
  while(i<MAXN){
    p=(p*b)%MOD;
    _pow[i] = p;
    i++;
  }
}

int main(){
  calcPow(2);
  fin>>n;
  for(int i=0; i<n; i++){
    fin>>v[i].a>>v[i].b;
    mars[v[i].a]++;
    mars[v[i].b+1]--;
  }
  for(int i=1; i<=2*n; i++){
    mars[i] += mars[i-1];
  }
  int total = 0;
  for(int i=0; i<n; i++){
    total = (total + _pow[n-mars[v[i].a]])%MOD;
  }
  fout<<total%MOD<<"\n";
  return 0;
}
