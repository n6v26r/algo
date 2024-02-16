#include <stdio.h>
#include <stdlib.h>
#define MAXN 1048576

int n, k;
int queue[MAXN+1], u, p;
int v[MAXN+1];

void add(int i, int ovveride){
  while(((ovveride && p!=u) ||(!ovveride && abs(p-u)>1)) && v[queue[p]]<=v[i]) p = (MAXN+p-1)%MAXN;
  p = p+1;
  queue[p] = i;
}

int main(){
  FILE *fin, *fout;
  fin = fopen("plfdgcb.in", "r");
  fscanf(fin, "%d %d\n", &n, &k);
  for(int i=0; i<n; i++)
    fscanf(fin, "%d\n", &v[i]);
  fclose(fin);

  int i = 1;
  int last = 0;
  long long sum = v[0];
  while(i<n){
    add(i, i-last<k);
    if(i-last==k){
      if(v[queue[u+1]]<v[queue[u+2]] && u+1!=p)
        u = u+1;
      sum += v[queue[u+1]];
      last = queue[u+1];
      u=u+1;
    }

    else if(v[queue[u+1]]>0){
      sum+=v[queue[u+1]];
      last = queue[u+1];
      u = (u+1)%MAXN;
    }

    i++;
  }

  if(p!=u)
    sum+=v[queue[p]];

  fout = fopen("plfdgcb.out", "w");
  fprintf(fout, "%lld\n", sum);
  fclose(fout);
  return 0;
}
