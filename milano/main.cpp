#include <iostream>
#include <algorithm>
#include <stdlib.h>
#include <set>
#include <string.h>
using namespace std;

#define MAXN 200000

int n, m;

typedef struct{
  int a;
  int b;
}p;

p v[MAXN+1];

int comp(p a, p b){
  return a.a<b.a;
}

int len[MAXN];
int maxfront[MAXN];

int main(){
  memset(maxfront, 127, sizeof(maxfront));
  freopen("file.in", "r", stdin);
  freopen("file.out", "w", stdout);
  scanf("%d", &n);
  for(int i=0; i<n; i++){
    scanf("%d", &v[i].a);
  }
  for(int i=0; i<n; i++){
    scanf("%d", &v[i].b);
  }

  sort(v, v+n, comp);
  //if(n>10) goto x;
  for(int i=0; i<n; i++){
    int maxlen = -1, maxpos = 0;
    //printf("%d %d: ", v[i].a, v[i].b);
    for(int j=0; j<n; j++){
      if(n-len[j]<v[i].b) continue;
      if(maxfront[j]<v[i].b) continue;
      //printf(">%d (%d %d)\n", j, maxfront[j], v[i].b);
      if(len[j]>maxlen){maxlen = len[j], maxpos = j;}
    }
    len[maxpos]++;
    //printf("%d\n", maxfront[maxpos]);
    maxfront[maxpos]--;
    if(v[i].b-1<maxfront[maxpos])maxfront[maxpos]=v[i].b-1;
    printf("%d (%d)\n", maxpos, maxfront[maxpos]);
  }

  //x:
  //if(n<=10){
    int total = 0;
    for(int i=0; i<n; i++){if(len[i]>0)total++;}
    printf("%d\n", total);
  /*}
  else{
    int i;
    for(i=0; i<n; i++){
      if(v[i].a+v[i].b-1!=n) break;
    }
    if(i<n) printf("2\n");
    else printf("1\n");
  }*/
  return 0;
}
