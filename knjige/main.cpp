#include <iostream>
#include <queue>

#define MAXN 200000
using namespace std;

int n, t, a, b;

long long v[MAXN+9];

int main(){
  //freopen("file.in", "r", stdin);
  //freopen("file.out", "w", stdout);
  scanf("%d%d%d%d", &n, &t, &a, &b);
  for(int i=0; i<n; i++){
    scanf("%lld", &v[i]);
    v[i]+=(i>0?v[i-1]:0);
  }
  long long maxins = 0;
  for(int i=0; b*i<t && i<n; i++){
    int rem = t-b*i; if(rem<a) break;
    int fullbooks = rem/a;
   // printf("%d\n", i+min(fullbooks, n-i)-1);
    long long ins = v[i+min(fullbooks, n-i)-1]-(i>0?v[i-1]:0);
    //printf("%d %d %d\n", i, fullbooks, ins);
    if(ins>maxins) maxins = ins;
  }
  printf("%lld\n", maxins);
  return 0;
}
