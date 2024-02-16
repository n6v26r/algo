#include <iostream>
#include <string.h>

#include <unistd.h>

#define MAXN 300003

using namespace std;

int t, n;

int maxst[MAXN];
int maxdr[MAXN];

int v[MAXN];

int main(){
  scanf("%d", &t);
  while(t>0){
    scanf("%d", &n);
    for(int i=0; i<n; i++){
      scanf("%d", &v[i]);
      //printf("%d ", v[i]);
    }
    for(int i=0; i<n; i++){
      if(abs(v[i+1]-v[i])<(abs((i>0?v[i-1]:1000000000)-v[i]))){
        int diff = abs(v[i+1]-v[i]);
        int j = i+2;
        while(j<n && abs(v[j]-v[j-1])<diff){diff=abs(v[j]-v[j-1]); j++;}
        int m = --j;
        while(j>=i){
          maxdr[j] = m; j--;
        }
        i = m-1;
      }
      else maxdr[i] = i;
    }
    for(int i=n-1; i>=0; i--){
      if(abs((i<n-1?v[i+1]:1000000000)-v[i])>(abs(v[i]-v[i-1]))){
        int diff = abs(v[i]-v[i-1]);
        int j = i-1;
        while(j>0 && abs(v[j]-v[j-1])<diff){diff=abs(v[j]-v[j-1]); j--;}
        int m = j;
        while(j<=i){
          maxst[j] = m; j++;
        }
        i = m+1;
      }
      else maxst[i] = i;
    }
    int m;
    scanf("%d", &m);
    for(int i=0; i<n; i++){
      int a, b;
      scanf("%d %d", &a, &b);
      a--;
      b--;
      long long cost=0;
      if(a<b){
        if(maxdr[a]>=b) cost+=abs(b-a), a=b;
        else{
          cost+=abs(a-maxdr[a]);
          a = maxdr[a];
        }
      }
      else{
        if(maxst[a]<=b) cost+=abs(a-b), a=b;
        else{
          cost+=abs(a-maxst[a]);
          a = maxst[a];
        }
      }
      cost+=abs(v[a]-v[b]);
      printf("%lld\n", cost);
    }
    t--;
  }
}
