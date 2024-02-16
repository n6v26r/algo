#include <iostream>
#include <algorithm>
#include <stdio.h>
using namespace std;

#define MAXN 300007

int n, m;

int v[MAXN];

int main(){
  //freopen("ccf.in", "r", stdin);
  //freopen("ccf.out", "w", stdout);
  scanf("%d\n", &n);
  char c = fgetc(stdin);
  int i = 0;
  int consec = 0;
  int _min = __INT_MAX__;
  int border = 1;
  int _minb = 0;
  int bord = -1;
  while(c!='\n'){
    if(c=='1'){
      consec++;
    }
    if(c=='0'){
      if(consec>=1 && consec<_min){
        _min = consec;
        if(border) _minb = _min-1;
        else _minb = 0;
      }
      consec = 0;
      border = 0;
    }
    v[i++] = c-'0';
    c = fgetc(stdin);
  }
  if(consec>=1 && consec<_min){
    _min = consec;
    _minb = _min-1;
  }
  int mc = __INT_MAX__;
 // printf(":%d\n", _minb);
  for(int x=0; x<=_minb; x++){
    int nig;
    int m = _min+x;
    //printf(">%d ", _minb);
    //printf("%d\n", m);
    //printf("|%d ", m);
    if(m%2) nig = m/2+1;
    else nig = m/2, m--;

    if(nig==0)nig = 1;

    //printf("nig: %d\n", nig);

    int cows = 0;
    for(int i=0; i<n; i++){
      if(v[i]==1){
        int j;
        for(j=i; j<n && v[j]==1; j++){};
        int len = j-i;
        //printf(">%d ", len);
        int a = len/(nig*2-1)+(len/(nig*2-1)>=1?(len%(nig*2-1)?1:0):len%(nig*2-1));
        if(i==0 || j==n){
          int l=len+1;
          while(l<=len+len-1){
            //printf("%d ", l);
            int b = l/(nig*2-1)+(l/(nig*2-1)>=1?(l%(nig*2-1)?1:0):l%(nig*2-1));
            a = min(a, b);
            l++;
          }
        }
        //printf("=> %d\n", a);
        cows += a;
        i = j;
      }
    }
    //printf("\n");
    //printf("=> %d\n", cows);
    if(cows<mc)
      mc = cows;
  }
  printf("%d\n", mc);
  return 0;
}
