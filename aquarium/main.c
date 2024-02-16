#include <stdio.h>

#define MAXSIZE 200000

long long t = 0, n, x;

long long v[MAXSIZE+1];

long long eval(long long h){
  long long sum = 0;
  for(long long i=0; i<n; i++){
    sum+=(h-v[i])*(h>v[i]);
  }
  return sum;
}

long long cautbin(long long *v, long long n, long long x){
  long long s=0, d=n;
  long long m;
  while(d-s>1){
    m = (d+s)/2;
//    printf("%d: %lld\n", m, eval(m));
    if(eval(m)>x)
      d=m;
    else
      s=m;
  }
  return s;
}

int main(){
  //freopen("file.in", "r", stdin);
  scanf("%lld", &t);
  while(t>0){
    long long max = 0;
    scanf("%lld %lld\n", &n, &x);
    for(long long i=0; i<n; i++){
      scanf("%lld", &v[i]);
      if(v[i]>max)max=v[i];
    }
    long long best = cautbin(v, max+x+1, x);
    if(best>0)
      printf("%lld\n", best);
    t--;
  }
  return 0;
}
