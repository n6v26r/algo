// ONI 2021 8th grade
// __razv was here
#include <iostream>
#include <stdio.h>
#include <string.h>

#define MAXN 100003
#define ABS(a) ((a)>0?(a):-(a))
#define MAX(a, b) ((a)>(b)?(a):(b))

int n, c;

int rest[2*MAXN];
int first[2*MAXN];
int last[2*MAXN];
long long sum[2*MAXN];
int v[MAXN];
long long sp[MAXN];

int main(){
  memset(first, -1, sizeof(first));
  memset(last, -1, sizeof(last));
  FILE *fin, *fout;
  fin = fopen("secvente.in", "r");
  fscanf(fin, "%d%d\n", &c, &n);
  long long total = 0;
  int maxlen = 0;
  long long maxsum = -__INT64_MAX__;
  rest[MAXN] = 1;
  first[MAXN] = 0;
  last[MAXN] = 0;
  for(int i=0; i<n; i++){
    fscanf(fin, "%d", &v[i]);
    sp[i] = (i>0?sp[i-1]:0)+v[i];
    // I
    total += rest[sp[i]%n+MAXN] + (-n+sp[i]%n == (-n+sp[i]%n)%n ? rest[(-n+sp[i]%n)%n+MAXN]:0);
    if(i>0 && (sp[i-1]%n==sp[i]%n || sp[i-1]%n == -n+sp[i]%n)) total--;
    else if(i==0 && sp[i]%n==0) total--;

    // II
    if(first[sp[i]%n+MAXN]!=-1 && maxlen<i-first[sp[i]%n+MAXN]+1) maxlen = i - first[sp[i]%n+MAXN]+1;
    if(first[(-n+sp[i]%n)%n+MAXN]!=-1 && maxlen<i-first[(-n+sp[i]%n)%n+MAXN]+1) maxlen = i - first[(-n+sp[i]%n)%n+MAXN]+1;

    // III
    sum[sp[i]%n+MAXN] = MAX(
                             sum[sp[i]%n+MAXN] + (last[sp[i]%n+MAXN]>=0?sp[i]-(last[sp[i]%n+MAXN]!=0?sp[last[sp[i]%n+MAXN]-1]:0):0),
                             sum[(-n+sp[i]%n)%n+MAXN] + (last[(-n+sp[i]%n)%n+MAXN]>=0?sp[i]-(last[(-n+sp[i]%n)%n+MAXN]!=0?sp[last[(-n+sp[i]%n)%n+MAXN]-1]:0):0)
                           );
    if(sum[sp[i]%n+MAXN]<0) sum[sp[i]%n+MAXN] = 0;
    maxsum = MAX(maxsum, sum[sp[i]%n+MAXN]);

    if(first[sp[i]%n+MAXN] == -1) first[sp[i]%n+MAXN] = i+1;
    last[sp[i]%n+MAXN] = i+1;
    rest[sp[i]%n+MAXN]++;
  }
  fclose(fin);

  fout = fopen("secvente.out", "w");
  if(c==1)
    fprintf(fout, "%lld\n", total);
  else if(c==2) fprintf(fout, "%d\n", maxlen);
  else fprintf(fout, "%lld\n", maxsum);
  fclose(fout);
  return 0;
}
