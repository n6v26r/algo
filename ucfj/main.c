#include <stdio.h>
#include <string.h>

#define MAXN 200001

int n;
int aib[MAXN];
int last[MAXN];

void update(int i, int val){
  while(i<=n){
    aib[i]+=val;
    i+=(i&(-i));
  }
}

long long get(int i){
  long long sum = 0;
  while(i>0){
    sum+=aib[i];
    i-=(i&(-i));
  }
  return sum;
}

int main(){
  memset(last, -1, sizeof(last));
  // freopen("file.in", "r", stdin);
  // freopen("file.out", "w", stdout);
  scanf("%d", &n);
  long long total=0;
  for(int i=0; i<n; i++){
    int val; scanf("%d", &val);
    if(last[val]!=-1){
      update(last[val]+1, -1);
    }
    total+=get(i) - get(last[val]);
    last[val] = i;
    update(i+1, 1);
  }
  printf("%lld\n", total);
  return 0;
}
