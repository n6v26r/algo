#include <iostream>
#include <bits/stdc++.h>
using namespace std;

#define MAXSIZE 500000

typedef struct{
  int a;
  int b;
}ab;

int n;
ab v[MAXSIZE+1];
long long sp[MAXSIZE+1];
int saveal[MAXSIZE+1];
int savear[MAXSIZE+1];

bool comp(ab a, ab b){
  return a.b<b.b;
}

int main(){
  cin>>n;
  for(int i=0; i<n; i++){
    cin>>v[i].a>>v[i].b;
  }
  sort(v, v+n, comp);
  int minkl = __INT_MAX__;
  for(int i=0; i<n; i++){
    sp[i] = (i>0?sp[i-1]:0)+v[i].b;
    if(v[i].a-v[i].b<minkl){
      minkl = v[i].a-v[i].b;
    }
    savear[i] = minkl;
  }

  int minkr = __INT_MAX__;
  for(int i=n-1; i>=0; i--){
    if(v[i].a<minkr){
      minkr = v[i].a;
    }
    saveal[i] = minkr;
  }

  for(int k=0; k<n; k++){
    long long a = ((k>0)?sp[k-1]:0)+saveal[k];
    long long b = sp[k]+savear[k];
    printf("%lld\n", min(a, b));
  }
  return 0;
}
