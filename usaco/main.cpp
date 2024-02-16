#include <iostream>
#include <algorithm>
#include <stdio.h>
#include <string.h>
using namespace std;

#define MAXN 100001

typedef struct{
  int a;
  int h;
} big;

int v[MAXN];
big w[MAXN];
int aib[MAXN];

int n, q, c, t;

void update(int i, int val, int n){
  while(i<=n){
    aib[i]+=val;
    i+=(i&(-i));
  }
}

int get(int i){
  int sum = 0;
  while(i>0){
    sum+=aib[i];
    i-=(i&(-i));
  }
  return sum;
}

bool comp(big a, big b){
  if(a.h!=b.h)
    return a.h<b.h;

  return a.a<b.a;
}

int main(){
  freopen("file.in", "r", stdin);
  freopen("file.out", "w", stdout);
  scanf("%d", &t);
  while(t>0){
    scanf("%d%d%d", &n, &q, &c);
    for(int i=0; i<n; i++)
      scanf("%d", &v[i]);
    for(int i=0; i<q; i++)
      scanf("%d %d", &w[i].a, &w[i].h), w[i].a--, w[i].h--;
    sort(w, w+q, comp);

    int j = 0;
    int i;
    for(i=0; i<n; i++){
      while(i==w[j].h && j<q){
        if(v[i]==0) v[i] = get(w[j].a)+1;
        else if(v[i]<get(w[j].a)+1){
          printf("-1\n"); break;
        }
        /*else{
          int y;
          for(int y=i; y>0 && v[y]!=0; y--){};
          int s = 0;
          int d = c;
          while(d-s>1){
            int m = (s+d)/2;
            if(get(w[j].h)<get(m)+1) d = m;
            else s = m;
          }
          update(0, -1, c);
          update(s, 1, c);
          v[y] = s;
        }*/
        if(j<q) j++;
      }
      if(i==w[j].h && j<q) break;
          //printf(":%d %d %d\n", i, v[i], s[i]);
      update(v[i], 1, c);
    }
    if(i>=n){
      for(int i=0; i<n; i++){
        printf("%d ", v[i]);
      }
      printf("\n");
    } fflush(stdout);
    t--;
  }
  return 0;
}
