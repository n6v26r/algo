#include <iostream>
#include <bits/stdc++.h>
using namespace std;

#define MAXN 100001

typedef struct{
  int a;
  int b;
  int k;
  int ord;
  int ans;
}querry;

int n, m;
int blocks;

int v[MAXN];
int f[2*MAXN+1];
int fk[MAXN+1];
querry q[MAXN];

bool comp(querry a, querry b){
  if(a.a/blocks!=b.a/blocks)
    return a.a/blocks<b.a/blocks;

  return a.b<b.b;
}

bool compOrd(querry a, querry b){
  return a.ord<b.ord;
}

void solve(int n, int m){
  blocks = sqrt(n);

  sort(q, q+m, comp);

  int left=0, right=0;

  for(int i=0; i<m; i++){
    int newLeft = q[i].a-1;
    int newRight = q[i].b-1;

    while(left<newLeft){
      fk[f[v[left]]]--;
      f[v[left]]--;
      fk[f[v[left]]]++;
      left++;
    }

    while(left>newLeft){
      fk[f[v[left-1]]]--;
      f[v[left-1]]++;
      fk[f[v[left-1]]]++;
      left--;
    }

    while(right<=newRight){
      fk[f[v[right]]]--;
      f[v[right]]++;
      fk[f[v[right]]]++;
      right++;
    }

    while(right>newRight+1){
      fk[f[v[right-1]]]--;
      f[v[right-1]]--;
      fk[f[v[right-1]]]++;
      right--;
    }

    q[i].ans = fk[q[i].k];
  }
}

int main(){
  ifstream fin("fsecv.in");
  ofstream fout("fsecv.out");
  fin>>n>>m;
  for(int i=0; i<n; i++)
    fin>>v[i];
  for(int i=0; i<m; i++){
    fin>>q[i].a>>q[i].b>>q[i].k;
    q[i].ord = i;
  }

  solve(n, m);
  sort(q, q+m, compOrd);
  for(int i=0; i<m; i++)
    fout<<q[i].ans<<endl;
  return 0;
}
