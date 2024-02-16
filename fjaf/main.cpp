#include <iostream>
#include <algorithm>
#include <stdio.h>
using namespace std;

#define MAXN 200007

typedef struct{
  long long h;
  long long a;
  long long v;
}st;

int t;
int n;
st v[MAXN];

bool comp(st a, st b){
  return a.h>b.h;
}

int main(){
  //freopen("ccf.in", "r", stdin);
  //freopen("ccf.out", "w", stdout);
  scanf("%d", &t);
  while(t>0){
    scanf("%d", &n);
    for(int i=0; i<n; i++){
      scanf("%lld", &v[i].h);
    }
    for(int i=0; i<n; i++){
      scanf("%lld", &v[i].a);
    }
    for(int i=0; i<n; i++){
      scanf("%lld", &v[i].v);
    }
    sort(v, v+n, comp);

   /* for(int i=0; i<n; i++)
      printf("{%d %d %d} ", v[i].h, v[i].a, v[i].v);
    printf("\n");*/

    int i;
    for(i=0; i<n; i++){
      if(v[i].v!=i || (v[i+1].h==v[i].h || v[i-1].h == v[i].h)) break;
    }
    if(i==n){
      printf("%d\n", 0);
    }
    else{
      int x = 0;
      while(x<20000){
        for(int i=0; i<n; i++){
          v[i].h+=v[i].a;
        }
        sort(v, v+n, comp);
        int i;
        for(i=0; i<n; i++){
          if(v[i].v!=i || (v[i+1].h==v[i].h || v[i-1].h == v[i].h)) break;
        }
        if(i==n){
          printf("%d\n", x+1);
          break;
        }
        x++;
      }
      if(x==20000)
        printf("-1\n");
    }
    t--;
  }
  return 0;
}
