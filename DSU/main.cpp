#include <iostream>
#include <algorithm>
using namespace std;

#define MAXN 1000

int sef[MAXN+1];
int sz[MAXN+1];
int sk[MAXN+1];

int f(int n){
  if(sef[n]==n)
    return n;

  return sef[n] = f(sef[n]);
}

void u(int a, int b){
  int u = f(a);
  int v = f(b);
  if(u==v) return;
  if(sz[u]<sz[v]){
    sef[u] = v;
    sz[v]+=sz[u];
  }else{
    sef[v] = u;
    sz[u] += sz[v];
  }
}

int main(){
  int n, m;
  scanf("%d%d", &n, &m);
  for(int i=0; i<=n; i++) sef[i] = i, sz[i] = 1;
  for(int i=0; i<m; i++){
    int a, b;
    scanf("%d %d", &a, &b);
    u(a, b);
    int j = 0;
    for(int i=1; i<=n; i++){
      if(f(i)==i)
        sk[j++] = sz[i];
    }
    sort(sk, sk+j);
    for(int i=0; i<j; i++)
      printf("%d ", sk[i]);
    printf("\n");
  }
  return 0;
}
