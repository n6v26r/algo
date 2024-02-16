#include <stdio.h>
#include <stdlib.h>

#define MAXN 200000

long long t=0;

long long v[MAXN+1];
long long h[MAXN+1];

int main(){
  //freopen("file.in", "r", stdin);
  scanf("%lld", &t);
  while(t>0){
    long long n, k;
    scanf("%lld%lld", &n, &k);
    for(long long i=0; i<n; i++){
      scanf("%lld", &v[i]);
    }
    for(long long i=0; i<n; i++){
      scanf("%lld", &h[i]);
    }
    long long s=0, d=0;
    long long max = 0;
    long long maxf = v[0];
    long long fruits = v[0];
    while(d+1<n && fruits>k){
      d++;
      s++;
      fruits=fruits-v[d-1]+v[d];
      maxf=fruits;
    }
    while(d+1<n){
      if(!(h[d]%h[d+1])){
        if(fruits+v[d+1]<=k){
          fruits+=v[d+1];
          d++;
        }
        else{
          fruits-=v[s];
          s++;
          if(s>d){
            d++;
            fruits+=v[d];
          }
          while(d+1<n && fruits>k){
            s++;
            fruits-=v[s];
            if(s>d){
              d++;
              fruits+=v[d];
            }
          }
        }
      }
      else{
        fruits = v[d]+v[d+1];
        d=d+1;
        s=d;
        while(d+1<n && fruits>k){
          s++;
          fruits-=v[s];
          if(s>d){
            d++;
            fruits+=v[d];
          }
        }
      }
      if(d-s>max && fruits<=k){
        max = d-s;
        maxf = fruits;
      }
      //printf("%lld %lld | (%lld %lld, %lld| %lld\n", s, d, h[d], h[d+1], fruits, max);
    }
    if(maxf<=k)
       printf("%lld\n", max+1);
    else
      printf("%d\n", 0);
    t--;
  }
  return 0;
}
