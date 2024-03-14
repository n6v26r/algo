#include <iostream>
using namespace std;

#define MAXN 1000001

int prime[100000];
char ciur[MAXN];

int main(){
  int j = 0;
  for(int i=2; i<MAXN; i++){
    if(!ciur[i]){
      for(long long d = (long long)i*i; d<MAXN; d+=i) ciur[d] = 1;
      prime[j++] = i;
    }
  }

  FILE *fin, *fout;
  fin = fopen("factorial.in", "r");
  fout = fopen("factorial.out", "w");
  char c = fgetc(fin);
  int n;
  while(c!=EOF && c!='\n'){
    ungetc(c, fin);
    fscanf(fin, "%d\n", &n);
    for(int i=0; i<j && prime[i]<=n; i++){
      int cnt = 0;
      int p = prime[i];
      long long e = p;
      while(e<=(long long)n){
        cnt+=n/e;
        e=e*p;
      }
      fprintf(fout, "%d ", cnt);
    }
    fprintf(fout, "\n");
    c = fgetc(fin);
  }
  fclose(fin);
  fclose(fout);

  return 0;
}
