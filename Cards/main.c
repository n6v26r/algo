#include <stdio.h>
#include <stdlib.h>

#define MAXN 200000

int v[MAXN];
long long save[MAXN];

int cmmdc(int a, int b){
  while(b!=0){
    int r = a%b;
    a = b;
    b = r;
  }
  return a;
}

long long getsum(int n, int k, long long s){
    if(save[k]) return save[k];
    if(!(n%k)){
        long long sum = 0;
        for(int i=0; i<n; i+=k)
            sum += v[i];
        save[k] = sum;
        return sum;
    }
    return getsum(n, cmmdc(n, k), s);
}

int main() {
    int n, i, k;
    long long s;

    scanf( "%d", &n );
    s = 0;
    for( i = 0; i < n; i++ ) {
        scanf( "%d", &v[i] );
        s += v[i];
    }
    for( k = 1; k <= n; k++ ) {
        printf("%lld\n", getsum(n, k, s)); 
    }
    return 0;
}
