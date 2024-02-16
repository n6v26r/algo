#include <stdio.h>
#include <iostream>
#include <bits/stdc++.h>

#define MAXN 100009

using namespace std;

int a[MAXN];
int b[MAXN];
int c[MAXN];

int t, n;

int main(){
  //freopen("file.in", "r", stdin);
  scanf("%d", &t);
  while(t>0){
    scanf("%d", &n);
    for(int i=0; i<n; i++){
      scanf("%d", &a[i]);
    }
    for(int i=0; i<n; i++){
      scanf("%d", &b[i]);
    }
    for(int i=0; i<n; i++){
      scanf("%d", &c[i]);
    }
    for(int i=0; i<n; i++){
      d[i] = a[i];
    }
    sort(d, d+n);
    printf("%d\n", d[n-1]+d[n-2]+d[n-3]);
    t--;
  }
  return 0;
}
