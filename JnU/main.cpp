#include <stdio.h>
#include <bits/stdc++.h>
using namespace std;

#define MAXN 100

int t, n, a;
int v[MAXN+1];

int main(){
  //freopen("file.in", "r", stdin);
  //freopen("file.out", "w", stdout);
  scanf("%d", &t);
  printf("%d ", &t);
  while(t>0){
    {
    scanf("%d %d %d", &a, &t, &n);
    for(int i=0; i<n; i++){
      scanf("%d\n", &v[i]);
    }
    sort(v, v+n);
    for(int i=0; i<n; i++){
      t += min(v[i], a);
    }
    printf("%d\n", t);
    }
    t--;
  }
  return 0;
}
