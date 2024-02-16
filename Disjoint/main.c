#include <stdio.h>
#include <stdlib.h>
#define MAXN 10001

typedef struct{
  int op;
  int a;
  int b;
}query;

typedef struct{
  int val;
  int ord;
}pair;

int sef[MAXN];
int sz[MAXN];

query q[MAXN];
pair v[2*MAXN+1];
int norm[MAXN];
int n;
int j;

int find(int n){
  if(sef[n]==n)
    return n;
  else return sef[n] = find(sef[n]);
}

void unite(int a, int b){
  int u = find(a);
  int v = find(b);
  if(u==v) return;
  if(sz[u]<sz[v]){
    sef[u] = v;
    sz[v] += sz[u];
  }
  else{
    sef[v] = u;
    sz[u] += sz[v];
  }
}

int compPair(const void* a, const void* b){
  pair _a = *((const pair*)a);
  pair _b = *((const pair*)b);

  return _a.val-_b.val;
}

int cautbin(int val){
  int s = 0;
  int d = j;
  while(d-s>1){
    int m = (s+d)/2;
    if(v[norm[m]].val>val) d=m;
    else s = m;
  }
  return s;
}

int main(){
  for(int i=0; i<MAXN; i++) sef[i] = i, sz[i] = 1;
  FILE *fin, *fout;
  fin = fopen("entries.in", "r");
  fout = fopen("entries.out", "w");
  fscanf(fin, "%d", &n);
  for(int i=0; i<n; i++){
    fscanf(fin, "%d%d%d", &q[i].a, &q[i].b, &q[i].op);
    v[2*i] = (pair){q[i].a, i*2};
    v[2*i+1] = (pair){q[i].b, i*2+1};
  }
  fclose(fin);
  qsort(v, 2*n, sizeof(pair), compPair);
  for(int i=0; i<2*n; i++){
    if(v[i].val==v[i-1].val) continue;
    norm[j++] = i;
  }
  for(int i=0; i<n; i++){
    if(q[i].op==1)
      unite(cautbin(q[i].a), cautbin(q[i].b));
    else if(q[i].op==2){
      if(find(cautbin(q[i].a))==find(cautbin(q[i].b))) fprintf(fout, "1\n");
      else fprintf(fout, "0\n");
    }
  }
  fclose(fout);
}
