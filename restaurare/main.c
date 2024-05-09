// ONI 2015 
// __razv was here
#include <stdio.h>

#define MAXN 100003
#define MAXQ MAXN

int n, q;

int v[MAXN];
int h[MAXN];

int query[MAXN];

int main(){
  FILE *fin, *fout;
  fin = fopen("restaurare.in", "r");
  fscanf(fin, "%d", &n);
  for(int i=0; i<n; i++) fscanf(fin, "%d", &v[i]);
  fscanf(fin, "%d", &q);
  for(int i=0; i<q; i++) fscanf(fin, "%d", &query[i]);
  fclose(fin);

  int MaxHight = MAXN-2;
  int last = MaxHight;
  for(int i=0; i<n; i++){
    if(v[i]>=last){last = v[i]; continue;}
    h[last]++;
    h[v[i]]--;
    last = v[i];
  }
  
  // MARS
  for(int i=MAXN-3; i>=0; i--){
    h[i] += h[i+1];
  }
  // SP
  for(int i=1; i<MAXN; i++){
    h[i] += h[i-1];
  }

  fout = fopen("restaurare.out", "w");
  for(int i=0; i<q; i++){
    fprintf(fout, "%d\n", h[query[i]]);
  }
  fclose(fout);
  return 0;
}
