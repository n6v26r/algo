#include <bits/stdc++.h>
#include <iostream>
#include <cmath>
using namespace std;

#define MAXN 300001

int n, k, q, l;
int v[MAXN];
int querry[MAXN];

int main(){
  cin>>n;
  cin>>k;
  FILE *fin, *fout;
  fin = fopen("kth1.in", "r");
  fscanf(fin, "%d%d%d", &n, &k, &l);
  for(int i=0; i<n; i++){
    fscanf(fin, "%d", &v[i]);
  }
  fscanf(fin, "%d", &q);
  for(int i=0; i<q; i++){
    fscanf(fin, "%d", &querry[i]);
  }
  sort(querry, querry+n);
  fclose(fin);

  fout = fopen("kth1.out", "w");
  fclose(fout);
  return 0;
}
