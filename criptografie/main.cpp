#include <stdio.h>
#include <string>
#define MAXN 100001

int p, n, k;

std::string v;
int frecv[128];

std::string best;

int main(){
  v.resize(MAXN);
  FILE *fin, *fout;
  fin = fopen("criptografie.in", "r");
  fscanf(fin, "%d%d%d\n", &p, &k, &n);
  for(int i=0; i<n; i++){
    v[i] = fgetc(fin);
  }
  fclose(fin);
  long long total = 0;
  int maxlen = 0;
  int s = 0;
  int d = 0;
  frecv[v[0]] = 1;
  while(s<n){
    while(d<n && frecv[v[d]]<=k){
      total += d-s+1;
      if(d-s+1>maxlen) maxlen = d-s+1, best = v.substr(s, d-s+1);
      else if(d-s+1==maxlen && v.substr(s, d-s+1)<best) best = v.substr(s, d-s+1);
      d++;
      frecv[v[d]]++;
    } 

    
   frecv[v[s]]--, s++;
  }

  fout = fopen("criptografie.out", "w");
  if(p==1)fprintf(fout, "%lld\n", total);
  else {
    for(int i=0; i<best.size(); i++)
      fprintf(fout, "%c", best[i]);
    fprintf(fout, "\n");
  }
  fclose(fout);
}
