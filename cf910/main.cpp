#include <iostream>
#include <bits/stdc++.h>
using namespace std;

#define MAXN 200001
#define EOL -1

int t, n, k;
int v[MAXN];
int nnext[2*MAXN];
int pprev[2*MAXN];
int main(){
  scanf("%d", &t);
  while(t>0){
    memset(pprev, 0, sizeof(pprev));
    memset(nnext, 0, sizeof(nnext));
    scanf("%d", &n);
    for(int i=1; i<=n; i++){
      scanf("%d", &v[i]);
      nnext[i-1] = i;
      pprev[i] = i-1;
    }
    nnext[n] = EOL;
    pprev[0] = EOL;
    int total = 0;
    int i = nnext[0];
    int j = n+1;
    /*for(int i=nnext[0]; i!=EOF; i=nnext[i]){
      printf("[%d]->", v[i]);
    }printf("\n");*/
    while(nnext[i]!=EOL){
      if(v[i]>v[nnext[i]]){
        int best = v[i]/2;
        int clone = v[i];
        v[i]=best;

        int aux = nnext[i];
        nnext[i] = j;
        pprev[j] = i;

        v[j] = clone-best;
        nnext[j] = aux;
        pprev[aux] = j;
        j++;

        i = pprev[pprev[i]];
        total++;

        /*for(int i=nnext[0]; i!=EOF; i=nnext[i]){
          printf("[%d]->", v[i]);
        }printf("\n");*/
      }
      i = nnext[i];
    }
    printf("%d\n", total);
    t--;
  }
  return 0;
}
