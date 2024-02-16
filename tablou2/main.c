#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAXN 20001

int p, n, z;
bool fl[MAXN];
bool fc[MAXN];

int main(){
  FILE *fin, *fout;
  fin = fopen("tablou2.in", "r");
  fscanf(fin, "%d\n%d %d\n", &p, &n, &z);
  if(p==1){
    for(int i=0; i<z; i++){
      char c = fgetc(fin);
      int nr;
      fscanf(fin, "%d\n", &nr);
      if(c=='L') fl[nr]=!fl[nr];
      else fc[nr]=!fc[nr];
    }
  }
  fclose(fin);

  fout = fopen("tablou2.out", "w");
  if(p==1){
    int l=0, c=0;
    for(int i=1; i<=n; i++){
      l+=fl[i];
      c+=fc[i];
    }
    fprintf(fout, "%lld\n", (long long)n*n-(l*n+c*n-2*l*c));
  }
  else{
    for(int l=0; l<=n; l++){
      if(n==2*l) continue;
      int c = (z-l*n)/(n-2*l);
      if((l*n+c*n-2*l*c)==z && c>=0 && c<=n){
        fprintf(fout, "%d\n", l+c);
        return 0;
      }
    }
    fprintf(fout, "0\n");
  }
  fclose(fout);
  return 0;
}
