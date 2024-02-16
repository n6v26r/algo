#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#define MAXN 100000
#define MIN(a, b) ((a<b)?(a):(b))
#define MAX(a, b) ((a>b)?(a):(b))

int n, k, m;

int mark[1000777];

int main(){
  int t;
  scanf("%d\n", &t);
  while(t>0){
    memset(mark, 0, sizeof(mark));
    scanf("%d%d%d\n", &n, &m, &k);
    if(n<k/2||m<k/2) {printf("NO\n"); continue;}
    for(int i=0; i<n; i++){
      int val;scanf("%d", &val);
      if(!mark[val]) mark[val] = 1;
    }
    for(int i=0; i<m; i++){
      int val; scanf("%d", &val);
      if(!mark[val]) mark[val] = 2;
      if(mark[val] == 1) mark[val] = 3;
    }

    int total=0, nex=0, mex=0;
    for(int i=1; i<=k; i++){
      if(!mark[i]) continue;
      total++;
      if(mark[i]==1) nex++;
      else if(mark[i]==2) mex++;
    }
    //printf("%d %d %d\n", total, nex, mex);
    if(total==k && (nex<=k/2 && mex<=k/2)) printf("YES\n");
    else printf("NO\n");
    t--;
  }
  return 0;
}
