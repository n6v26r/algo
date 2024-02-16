#include <iostream>
#include <bits/stdc++.h>
using namespace std;

int t;

int v[200001];

int main(){
  scanf("%d\n", &t);
  while(t>0){
    int n;
    scanf("%d", &n);
    int _min=INT_MAX, minpos=0;
    for(int i=0; i<n; i++){
      scanf("%d", &v[i]);
      if(v[i]<_min){
        _min = v[i];
        minpos = i;
      }
    }
    int i;
    for(i=minpos+1; i<n; i++){
      if(v[i]<v[i-1]) break;
    }
    if(i<n) printf("-1\n");
    else printf("%d\n", minpos);
    t--;
  }
  return 0;
}
