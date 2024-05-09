#include <stdio.h>

long long n;
long long div[100000];

long long euler(long long n){
  long long d = 2;
  long long e = n;
  while(d*d<=n){
    if(n%d==0){
      e = e/d*(d-1);
      while(n%d==0) n/=d;
    }
    d++;
  }
  if(n>1) e = e/n*(n-1);
  return e;
}

__int128 pw(__int128 b, __int128 e){
  __int128 p = 1;
  while(e>0){
    if(e%2) p = (p*b)%n;
    b = (b*b)%n;
    e/=2;
  }
  return p;
}

int main(){
  FILE *fin, *fout;
  fin = fopen("perioada.in", "r");
  fscanf(fin, "%lld", &n);
  fclose(fin);

  long long e = euler(n);
  int j = 0;
  __int128 mod = 1;
  long long p = 0;
  
  long long i;
  fout = fopen("perioada.out", "w");
  for(i=1; i*i<=e; i++){
    if(e%i>0) continue;
    mod = (mod * pw(10, i-p))%n;
    if(pw(10, i-p)<0) return 0;
    p = i;
    if(mod==1){fprintf(fout,"%lld\n", i);break;}
    div[j++] = e/i;
  }
  if(i*i<=e){fclose(fout);return 0;}
  for(int i=j-1; i>=0; i--){
    if(e%div[i]>0) continue;

    mod = (mod * pw(10, div[i]-p))%n;
    p = div[i];
    if(mod==1){fprintf(fout,"%lld\n", div[i]);break;}
  } 

  fclose(fout);
}
