#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#define MAXN 50069

int n, p;
int numar[20]; int cif;
long long v[MAXN];
long long ans[MAXN];
int secv[MAXN];

int max;
long long bestStart = 0;

long long palindrom(long long val){
  int cif = 0;
  long long p10=1; while(p10*10<val) p10*=10, cif++;
  long long leftside = 0;
  int lcif = 0;
  while(lcif<=cif/2){
    leftside = leftside * 10 + val/p10;
    val%=p10;
    p10/=10;
    lcif++;
  }

  long long r = val;
  long long invR = 0;
  while(val>0){
    invR = invR * 10 + val%10;
    val/=10;
  }

  long long center = leftside%10;
  leftside/=10;

  long long l = leftside;
  long long invL = 0;
  while(l>0){
    invL = invL * 10 + l%10;
    l/=10;
  }

  if(invL<r){
    center++;
    if(center>9){center=0; leftside++;}
  }
    
  invR = leftside;

  long long pal = leftside*10+center;
  while(invR>0){
    pal = pal*10+invR%10;
    invR/=10;
  }

  return pal;
}

int compLL(const void* a, const void* b){
  long long _a = *((const long long*)a);
  long long _b = *((const long long*)b);

  return _a>_b?(1):(_a==_b?0:-1);
}

long long cautbin(long long val){
  int s = 0;
  int d = n;
  while(d-s>1){
    int m = (s+d)/2;
    if(v[m]>val) d = m;
    else s = m;
  }
  return s;
}

int main(){
  FILE *fin, *fout;
  fin = fopen("pal.in", "r");
  fout = fopen("pal.out", "w");
  fscanf(fin, "%d%d\n", &p, &n);
  for(int i=0; i<n; i++){
    long long val; fscanf(fin, "%lld", &val);
    val = palindrom(val);
    if(p==1) fprintf(fout, "%lld ", val);
    v[i] = val;
  }
  fclose(fin);

  if(p==1) return 0; // bye bye
  qsort(v, n, sizeof(long long), compLL);
  for(int i=n-1; i>=0; i--){
    long long val = v[i];
    long long p10 = 1; while(p10*10<=val) p10*=10;
    while(p10>0){
      secv[i] += v[cautbin(val)]==val;
      if(secv[i]>max){
        max = secv[i];
        bestStart = i;
      }
      val = val%p10;
      val/=10;
      p10/=100;
    }
  }
  
  if(p==2) fprintf(fout, "%d", max);
  else{
    int i = 0;
    long long val = v[bestStart];
    long long p10 = 1; while(p10*10<=val) p10*=10;
    while(p10>0){
      if(v[cautbin(val)]==val) ans[i++] = val;
      val = val%p10;
      val/=10;
      p10/=100;
    }
    for(int j=i-1; j>=0; j--) fprintf(fout, "%lld ", ans[j]);
  }
  fprintf(fout, "\n");
  fclose(fout);
  return 0;
}