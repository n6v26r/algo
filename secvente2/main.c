#include <stdio.h>
#include <string.h>

#define MAXN 15001
#define MAXVAL 30009

int n, k, t, p;

int v[MAXN];
int first[MAXN];
int ciur[MAXVAL];

void _ciur(){
  for(int i = 2; i*i<MAXVAL; i++)
    if(!ciur[i])
      for(int d=i*i; d<MAXVAL; d+=i)
        ciur[d] = 1;
  ciur[1]=ciur[0] = 1;
}

int main(){
  _ciur();
  FILE *fin, *fout;
  fin = fopen("secvente.in", "r");
  fout = fopen("secvente.out", "w");
  fscanf(fin, "%d", &t);  
  while(t>0){
    memset(v, 0, sizeof(v));
    memset(first, 0, sizeof(first));
    fscanf(fin, "%d%d%d", &n, &p, &k);
    int total = 0;
    int max = 0;
    for(int i=0; i<n; i++){
      int val;
      fscanf(fin, "%d", &val);
      while(!(val%p) && val/p>1)
        val/=p;
      if(ciur[val]) v[i] = (i>0?v[i-1]:0);
      else{
        v[i] = (i>0?v[i-1]+1:1);
        first[v[i]] = i;
        max = v[i];
        if(v[i]<k) continue;
        total++;
      }
    }
    fprintf(fout, "%d\n", total);
    for(int i=k; i<=max; i++){
      int a = first[i-k+1];
      fprintf(fout, "%d %d\n", a+1, first[i]+1);
    }
    t--;
  }
  fclose(fin);
  fclose(fout);
  return 0;
}
