// OJI 2023 - 8th grade
#include <stdio.h>
#include <string.h>

#define MAXN 100001
#define MAXVAL 1000001

int t, n; unsigned long long k;
int v[MAXN];
long long sp[MAXN];
long long sc[MAXN];
int ciur[MAXVAL];
int first[MAXVAL];
int last[MAXVAL];
int prime[MAXVAL/5];
int frecv[MAXVAL/10];

unsigned long long getCost(int i, int j){
  long long p = sp[j] - (i>0?sp[i-1]:0);
  long long c = sc[j] - (i>0?sc[i-1]:0);
  return (unsigned long long)p*c;
}

int cautbin(int pos, unsigned long long val){
  int s = pos;
  int d = n;
  while(d-s>1){
    int m = (s+d)/2;
    if(getCost(pos, m)>val) d = m;
    else s = m;
  }
  return s;
}

int main(){
  memset(first, -1, sizeof(first));
  memset(last, -1, sizeof(last));
  int j = 0;
  for(int i=2; i<MAXVAL; i++){
    if(!ciur[i]){
      first[i] = 1; last[i] = i;
      for(int d=2*i; d<MAXVAL; d+=i){
        ciur[d] = 1;
        last[d] = i;
        if(first[d]==-1) first[d] = i;
      }
      prime[j++] = i;
    }
  }
  ciur[1] = 1; first[1] = 1, last[1] = 1;

  for(int i= 0; i<100; i++)printf("%d. %d %d\n", i, first[i], last[i]);

  FILE *fin, *fout;
  fin = fopen("tema.in", "r");
  fscanf(fin, "%d%d%llu", &t, &n, &k);
  for(int i=0; i<n; i++){
    fscanf(fin, "%d", &v[i]);
    if(!ciur[v[i]]) sp[i]=(i>0?sp[i-1]:0) + v[i], sc[i] = (i>0?sc[i-1]:0);
    else{
      sp[i] = (i>0?sp[i-1]:0);
      if(v[i]!=1) sc[i] = (i>0?sc[i-1]:0) + v[i];
      else sc[i] = (i>0?sc[i-1]:0);
    }
  }
  fclose(fin);

  int max = 0, maxa = -1, maxb = -1;
  if(t==1){
    for(int i=0; i<n; i++){
      int j = cautbin(i, k);
      if(j-i+1>max) max = j-i+1;
    }
  }
  else{
    int i = 0;
    while(v[i]==1) i++;
    j = i;
    frecv[first[v[i]]]++; if(last[v[i]]!=first[v[i]]) frecv[last[v[i]]]++;
    while(i<n){
      if(j<i){ 
        frecv[first[v[i]]]++; if(last[v[i]]!=first[v[i]]) frecv[last[v[i]]]++;
        j = i;
      }
      do{
        j++;
        frecv[first[v[j]]]++; if(last[v[j]]!=first[v[j]]) frecv[last[v[j]]]++;
      }while(j<n && frecv[first[v[i]]]==j-i+1 || frecv[last[v[i]]]==j-i+1);
      
      frecv[first[v[j]]]--; if(last[v[j]]!=first[v[j]]) frecv[last[v[j]]]--;

      int len = j-i;
      if(len>max){max = len; maxa = i; maxb = j-1;}
      else if(len==max && i>maxa){maxa = i; maxb = j-1;}

      frecv[first[v[i]]]--; if(last[v[i]]!=first[v[i]]) frecv[last[v[i]]]--;
      j--;
      i++;
    }
  }

  fout = fopen("tema.out", "w");
  if(t==1) fprintf(fout, "%d\n", max);
  else fprintf(fout, "%d %d\n", maxa+1, maxb+1);
  fclose(fout);
  return 0;
}
