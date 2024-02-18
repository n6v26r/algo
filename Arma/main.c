#include <stdio.h>
#include <limits.h>

#define MAXN 10001
#define RADMAXVAL 45069

int c, n;
int ciur[RADMAXVAL];
int prime[RADMAXVAL];

int cmmdc(int a, int b){
  while(b>0){
    int r = a%b;
    a = b;
    b = r;
  }
  return a;
}

int div(int n){
  int j = 0;
  int d = prime[j++];
  int cmd = -1;
  while(d*d<=n){
    int exp = 0;
    while(n%d==0) n/=d, exp++;
    if(exp>0){
      if(cmd==-1) cmd = exp;
      else cmd = cmmdc(cmd, exp); 
    }
    d = prime[j++];
  }
  if(n>1) cmd = 1;
  return cmd;
}

long long _pow(long long b, int e){
  long long p = 1;
  while(e>0){
    if(e%2) p*=b;
    b*=b;
    e/=2;
    if( (b>INT_MAX && e>0) || p>INT_MAX) return INT_MAX;
  }
  return p;
}

int cautbin(int p, int val){
  long long s = 0;
  long long d = val+1;
  while(d-s>1){
    long long m = (s+d)/2;
    if(_pow(m, p)>(long long)val) d = m;
    else s = m;
  }
  return s;
}

int main(){
  int j = 0;
  for(int i=2; i<RADMAXVAL; i++){
    if(!ciur[i]){
      for(int d=i*i; d<RADMAXVAL; d+=i) ciur[d] = 1; 
      prime[j++] = i;
    }
  }
  FILE *fin, *fout;
  fin = fopen("arma1.in", "r");
  fout = fopen("arma1.out", "w");
  fscanf(fin, "%d%d", &c, &n);
  long long sum = 0;
  for(int i=0; i<n; i++){
    int val; fscanf(fin, "%d", &val);
    int p = div(val);
    if(c==2) fprintf(fout, "%d\n", p);
    else sum+=cautbin(p, val);
  }
  if(c==1)
    fprintf(fout, "%lld\n", sum);
  fclose(fin);
  fclose(fout);
  return 0;
}